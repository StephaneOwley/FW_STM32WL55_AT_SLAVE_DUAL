/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sigfox_mbwrapper.c
  * @author  MCD Application Team
  * @brief   This file implements the CM0 side wrapper of the sigfoxMac interface
  *          shared between M0 and M4.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "sigfox_mbwrapper.h"
#include "stm32_mem.h"
#include "stm32_seq.h"
#include "mbmux_table.h"
#include "msg_id.h"
#include "mbmux.h"
#include "mbmuxif_sigfox.h"
#include "sys_app.h"
#include "st_sigfox_api.h"
#include "sigfox_monarch_api.h"
#include "sigfox_info.h"
#include "utilities_def.h"
#include "stm32_timer.h"
// test
#include "radio.h"
extern RadioEvents_t RfApiRadioEvents;
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define SIZE_CONF_WORDS 3
#define SGFX_MAX_PAYLOAD_SIZE 12
#define SGFX_DWNL_SIZE 8

#define SIGFOX_MBWRAP_SHBUF_SIZE        SGFX_MAX_PAYLOAD_SIZE*sizeof(sfx_u8)

/* USER CODE BEGIN PD */
// ---- CODE OWLEY GEOLOC ----
typedef enum { LOC_STATE_OFF = 0, LOC_STATE_ON } loc_state_t;

static UTIL_TIMER_Object_t LocTimer;    // Timer RTC (UTILS ST)
static volatile loc_state_t locState;
static uint32_t locFreq;
static int32_t  locPower_dbm;           // signe si besoin (dBm)
static bool     locActive = false;

static void LOC_TimerCb(void *arg)
{
  (void)arg;

  if (!locActive) return;

  if (locState == LOC_STATE_OFF) {
    // PASSAGE -> ON
    Radio.SetChannel(locFreq);
    Radio.TxCw((uint32_t)locPower_dbm);     // démarre la porteuse CW
    locState = LOC_STATE_ON;
    UTIL_TIMER_SetPeriod(&LocTimer, 90);    // 90 ms
    UTIL_TIMER_Start(&LocTimer);
  } else {
    // PASSAGE -> OFF
    Radio.Standby();                        // ou Radio.Sleep()
    locState = LOC_STATE_OFF;
    UTIL_TIMER_SetPeriod(&LocTimer, 3000);  // 3000 ms
    UTIL_TIMER_Start(&LocTimer);
  }
}
// ---- CODE OWLEY GEOLOC ----

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UTIL_MEM_PLACE_IN_SECTION("MB_MEM3") uint8_t aSigfoxMbWrapShare2Buffer[SIGFOX_MBWRAP_SHBUF_SIZE];

/* USER CODE BEGIN PV */
// ---- CODE OWLEY GEOLOC ----
void LOC_InitOnce(void)
{
  static bool inited = false;
  if (inited) return;
  inited = true;

  // Timer périodique basé RTC (fourni par ST dans Utilities)
  UTIL_TIMER_Create(&LocTimer, 0, UTIL_TIMER_ONESHOT, LOC_TimerCb, NULL);
}
// ---- CODE OWLEY GEOLOC ----
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/*!
  * @brief This is the function that will be called by the Sigfox Library when the scan is completed
  * @param[out] rc_bit_mask  rc  Value of the RC found. There could be only 1 RC or 0 ( not found )
  * @param[out] rssi         RSSI value of the RC found. if rc = 0, rssi is not valid ( is set to 0 too )
  */
static sfx_u8 app_monarch_rcscan_wrapper(sfx_u8 rc_bit_mask, sfx_s16 rssi);

/**
  * @brief  rf test mode call back starting a while wait loop
  */
static void sfx_monarch_test_mode_wait_start_cb(void);

/**
  * @brief  rf test mode call back exiting a while wait loop
  */
static void sfx_monarch_test_mode_wait_end_cb(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
void Process_Sigfox_Cmd(MBMUX_ComParam_t *ComObj)
{
  /* USER CODE BEGIN Process_Sigfox_Cmd_1 */

  /* USER CODE END Process_Sigfox_Cmd_1 */
  uint32_t *com_buffer = NULL;
  sfx_u32 config_words[SIZE_CONF_WORDS];
  sfx_u8 frame_ul[SGFX_MAX_PAYLOAD_SIZE];
  sfx_u8 frame_dwnl[SGFX_DWNL_SIZE];

  sfx_error_t status;

  /* init */

  APP_LOG(TS_ON, VLEVEL_H, " * CM0PLUS Sigfox command received\n\r");

  com_buffer = MBMUX_SEC_VerifySramBufferPtr(ComObj->ParamBuf, ComObj->BufSize);

  /* process Command */
  switch (ComObj->MsgId)
  {
    case SIGFOX_START_ID:
      status = SIGFOX_API_open((sfx_rc_t *)com_buffer[0]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_STOP_ID:
      status = SIGFOX_API_close();
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_SEND_FRAME_DWNL_ID:
      UTIL_MEM_cpy_8((uint8_t *)frame_ul, (uint8_t *)com_buffer[0], SGFX_MAX_PAYLOAD_SIZE * sizeof(sfx_u8));
      UTIL_MEM_cpy_8((uint8_t *)frame_dwnl, (uint8_t *)com_buffer[2], SGFX_DWNL_SIZE * sizeof(sfx_u8));

      status = SIGFOX_API_send_frame((sfx_u8 *)frame_ul, (sfx_u8)com_buffer[1], (sfx_u8 *)frame_dwnl, (sfx_u8)com_buffer[3], (sfx_bool)com_buffer[4]);

      UTIL_MEM_cpy_8((uint8_t *)com_buffer[0], (uint8_t *)frame_ul, SGFX_MAX_PAYLOAD_SIZE * sizeof(sfx_u8));
      UTIL_MEM_cpy_8((uint8_t *)com_buffer[2], (uint8_t *)frame_dwnl, SGFX_DWNL_SIZE * sizeof(sfx_u8));

      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_SEND_BIT_ID:
      UTIL_MEM_cpy_8((uint8_t *)frame_dwnl, (uint8_t *)com_buffer[1], SGFX_DWNL_SIZE * sizeof(sfx_u8));

      status = SIGFOX_API_send_bit((sfx_bool)com_buffer[0], (sfx_u8 *)frame_dwnl, (sfx_u8)com_buffer[2], (sfx_bool)com_buffer[3]);

      UTIL_MEM_cpy_8((uint8_t *)com_buffer[1], (uint8_t *)frame_dwnl, SGFX_DWNL_SIZE * sizeof(sfx_u8));
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_SEND_OOB_ID:
      status =  SIGFOX_API_send_outofband((sfx_oob_enum_t) com_buffer[0]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_SET_STD_ID:
      UTIL_MEM_cpy_8((uint8_t *)config_words, (uint8_t *)com_buffer[0], SIZE_CONF_WORDS * sizeof(sfx_u32));

      status = SIGFOX_API_set_std_config(config_words, (sfx_bool) com_buffer[1]);

      UTIL_MEM_cpy_8((uint8_t *)com_buffer[0], (uint8_t *)config_words, SIZE_CONF_WORDS * sizeof(sfx_u32));
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_START_CONTINUOUS_ID:
      // debut test
      if ((sfx_modulation_type_t)com_buffer[1]== 0)
      {
    	  APP_LOG(TS_ON, VLEVEL_M, "INIT RF\r");
    	  Radio.Init(&RfApiRadioEvents);
    	  APP_LOG(TS_ON, VLEVEL_M, "SETCHANNEL RF at Freq %d\n\r",(sfx_u32)com_buffer[0]);
    	  Radio.SetChannel((sfx_u32)com_buffer[0]);
    	  Radio.SetTxContinuousWave((sfx_u32)com_buffer[0], 15, 10000);
    	  //Radio.TxCw(15);
    	  // fin test
    	  status = 0;
      }
      else
      {
      status = SIGFOX_API_start_continuous_transmission((sfx_u32)com_buffer[0], (sfx_modulation_type_t)com_buffer[1]);
      }
      // test
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_STOP_CONTINUOUS_ID:
      // Test
      // stop timer if any
      locActive = false;
      UTIL_TIMER_Stop(&LocTimer);
      // end stop timer if any
      Radio.Init(&RfApiRadioEvents);
      // test
      status = SIGFOX_API_stop_continuous_transmission();
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case OWLEY_LOC_ID:
      /* SYNCHRINOUS VERSION
      APP_LOG(TS_ON, VLEVEL_M, "INIT OWLEY GEOLOC_1\r");
      Radio.Init(&RfApiRadioEvents);
      APP_LOG(TS_ON, VLEVEL_M, "SETCHANNEL OWLEY GEOLOC at Freq %d\n\r",(sfx_u32)com_buffer[0]);
      Radio.SetChannel((sfx_u32)com_buffer[0]);
      APP_LOG(TS_ON, VLEVEL_M, "SETPOWER OWLEY GEOLOC at %d\n\r",(sfx_u32)com_buffer[1]);
      Radio.SetTxContinuousWave((sfx_u32)com_buffer[0], (sfx_u32)com_buffer[1], 3);
      Radio.TxCw((sfx_u32)com_buffer[1]);
      */
      status = 0;
      /* ASYNCHRONOUS VERSION */
      /* prepare response buffer */
      uint32_t freq  = com_buffer[0];
      int32_t  power = (int32_t)com_buffer[1];   // dBm recommandé
   	  // Sécurités minimales
   	  if (!(freq > 100000000UL && freq < 1000000000UL)) {
   	    ComObj->ParamCnt = 0; ComObj->ReturnVal = (uint32_t) status; break;
   	  }
   	  APP_LOG(TS_ON, VLEVEL_M, "INIT OWLEY GEOLOC_1\r");
      LOC_InitOnce();
      // Mettre la radio dans un état propre UNE FOIS
      Radio.Init(&RfApiRadioEvents);

      locFreq       = freq;
      locPower_dbm  = power;
      locState      = LOC_STATE_OFF;
      locActive     = true;
      APP_LOG(TS_ON, VLEVEL_M, "SETCHANNEL OWLEY GEOLOC at Freq %d\n\r",(sfx_u32)com_buffer[0]);
      APP_LOG(TS_ON, VLEVEL_M, "SETPOWER OWLEY GEOLOC at %d\n\r",(sfx_u32)com_buffer[1]);
      // Démarrer la séquence non bloquante : premier déclenchement immédiat
      UTIL_TIMER_Stop(&LocTimer);
      UTIL_TIMER_SetPeriod(&LocTimer, 1);   // 1 ms pour armer le premier ON
      UTIL_TIMER_Start(&LocTimer);
      // Réponse immédiate au CM4 : OK, la séquence tourne en tâche de fond
      ComObj->ParamCnt = 0;
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_GET_VERSION_ID:
      status = SIGFOX_API_get_version((sfx_u8 **) com_buffer[0], (sfx_u8 *) com_buffer[1], (sfx_version_type_t)com_buffer[2]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_GET_DEVICE_ID:
      status = SIGFOX_API_get_device_id((sfx_u8 *) com_buffer[0]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_GET_INIT_PAC_ID:
      status = SIGFOX_API_get_initial_pac((sfx_u8 *) com_buffer[0]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_SET_RCSYNC_PERIOD_ID:
      status = SIGFOX_API_set_rc_sync_period((sfx_u16) com_buffer[0]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_API_TEST_MODE_ID:
      status = ADDON_SIGFOX_RF_PROTOCOL_API_test_mode((sfx_rc_enum_t) com_buffer[0], (sfx_test_mode_t) com_buffer[1]);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_API_MONARCH_TEST_MODE_ID:
      status = ST_ADDON_SIGFOX_RF_PROTOCOL_API_monarch_test_mode_async((sfx_rc_enum_t) com_buffer[0], (sfx_test_mode_t) com_buffer[1], (sfx_u8)  com_buffer[2],
                                                                       sfx_monarch_test_mode_wait_start_cb,
                                                                       sfx_monarch_test_mode_wait_end_cb);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_API_MONARCH_TEST_EXEC_RC_SCAN_ID:
      status = SIGFOX_MONARCH_API_execute_rc_scan((sfx_u8) com_buffer[0], (sfx_u16) com_buffer[1], (sfx_timer_unit_enum_t)  com_buffer[2],
                                                  app_monarch_rcscan_wrapper);
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_API_MONARCH_STOP_RC_SCAN_ID:
      status = SIGFOX_MONARCH_API_stop_rc_scan();
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = (uint32_t) status;
      break;

    case SIGFOX_INFO_INIT_ID:
      SigfoxInfo_Init();
      /* prepare response buffer */
      ComObj->ParamCnt = 0; /* reset ParamCnt */
      ComObj->ReturnVal = 0; /* */
      break;

    default:
      break;
  }

  /* send Response */
  APP_LOG(TS_ON, VLEVEL_H, " * CM0PLUS Sigfox sending response\n\r");
  MBMUX_ResponseSnd(FEAT_INFO_SIGFOX_ID);
  /* USER CODE BEGIN Process_Sigfox_Cmd_2 */

  /* USER CODE END Process_Sigfox_Cmd_2 */
}

uint16_t GetBatteryLevel_mbwrapper(void)
{
  /* USER CODE BEGIN GetBatteryLevel_mbwrapper_1 */

  /* USER CODE END GetBatteryLevel_mbwrapper_1 */
  MBMUX_ComParam_t *com_obj;
  uint32_t ret;

  com_obj = MBMUXIF_GetSigfoxFeatureNotifComPtr();
  com_obj->MsgId = SIGFOX_GET_BATTERY_LEVEL_CB_ID;
  com_obj->ParamCnt = 0;
  /* Don't call MBMUXIF_SigfoxSendNotif to force blocking DAC computation in CM4
    to display value on CM0 */
  MBMUXIF_SigfoxSendNotifTask();
  /* waiting for event */
  /* once event is received and semaphore released: */
  ret = com_obj->ReturnVal;
  return (uint16_t) ret;
  /* USER CODE BEGIN GetBatteryLevel_mbwrapper_2 */

  /* USER CODE END GetBatteryLevel_mbwrapper_2 */
}

int16_t GetTemperatureLevel_mbwrapper(void)
{
  /* USER CODE BEGIN GetTemperatureLevel_mbwrapper_1 */

  /* USER CODE END GetTemperatureLevel_mbwrapper_1 */
  MBMUX_ComParam_t *com_obj;
  uint32_t ret;

  com_obj = MBMUXIF_GetSigfoxFeatureNotifComPtr();
  com_obj->MsgId = SIGFOX_GET_TEMPERATURE_LEVEL_CB_ID;
  com_obj->ParamCnt = 0;
  /* Don't call MBMUXIF_SigfoxSendNotif to force blocking DAC computation in CM4
  to display value on CM0 */
  MBMUXIF_SigfoxSendNotifTask();
  /* waiting for event */
  /* once event is received and semaphore released: */
  ret = com_obj->ReturnVal;
  return (int16_t) ret;
  /* USER CODE BEGIN GetTemperatureLevel_mbwrapper_2 */

  /* USER CODE END GetTemperatureLevel_mbwrapper_2 */
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private Functions Definition -----------------------------------------------*/
static sfx_u8 app_monarch_rcscan_wrapper(sfx_u8 rc_bit_mask, sfx_s16 rssi)
{
  /* USER CODE BEGIN app_monarch_rcscan_wrapper_1 */

  /* USER CODE END app_monarch_rcscan_wrapper_1 */
  MBMUX_ComParam_t *com_obj;
  uint32_t *com_buffer = NULL;
  uint32_t ret;

  com_obj = MBMUXIF_GetSigfoxFeatureNotifComPtr();
  com_obj->MsgId = SIGFOX_MONARCH_RC_SCAN_CB_ID;

  com_buffer = MBMUX_SEC_VerifySramBufferPtr(com_obj->ParamBuf, com_obj->BufSize);
  com_buffer[0] = (uint32_t) rc_bit_mask;
  com_buffer[1] = (uint32_t) rssi;
  com_obj->ParamCnt = 2;
  MBMUXIF_SigfoxSendNotif();
  /* waiting for event */
  /* once event is received and semaphore released: */
  ret = com_obj->ReturnVal;
  return (sfx_u8) ret;
  /* USER CODE BEGIN app_monarch_rcscan_wrapper_2 */

  /* USER CODE END app_monarch_rcscan_wrapper_2 */
}

static void sfx_monarch_test_mode_wait_start_cb(void)
{
  /* USER CODE BEGIN sfx_monarch_test_mode_wait_start_cb_1 */

  /* USER CODE END sfx_monarch_test_mode_wait_start_cb_1 */

  /* don't exit this function until test_mode_wait_end callback is called */
  UTIL_SEQ_WaitEvt(1 << CFG_SEQ_Evt_Monarch);

  /* USER CODE BEGIN sfx_monarch_test_mode_wait_start_cb_2 */

  /* USER CODE END sfx_monarch_test_mode_wait_start_cb_2 */
}

static void sfx_monarch_test_mode_wait_end_cb(void)
{
  /* USER CODE BEGIN sfx_monarch_test_mode_wait_end_cb_1 */

  /* USER CODE END sfx_monarch_test_mode_wait_end_cb_1 */

  /* release from the test_mode_wait */
  UTIL_SEQ_SetEvt(1 << CFG_SEQ_Evt_Monarch);

  /* USER CODE BEGIN sfx_monarch_test_mode_wait_end_cb_2 */

  /* USER CODE END sfx_monarch_test_mode_wait_end_cb_2 */
}
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */
