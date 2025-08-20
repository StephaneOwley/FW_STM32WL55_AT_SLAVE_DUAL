/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    mbmuxif_owley.c
  * @author  Owley Team
  * @brief   allows CM4 application to register and handle Owley via MBMUX
  ******************************************************************************
  * @attention
  *
  * Copyright Owley.
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "mbmuxif_owley.h"
#include "mbmuxif_sys.h"
#include "sys_app.h"
#include "stm32_mem.h"
#include "stm32_seq.h"
#include "owley_mbwrapper.h"
#include "app_version.h"
#include "utilities_def.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static MBMUX_ComParam_t *OwleyComObj;

UTIL_MEM_PLACE_IN_SECTION("MB_MEM1") uint32_t aOwleyCmdRespBuff[MAX_PARAM_OF_OWLEY_CMD_FUNCTIONS];/*shared*/
UTIL_MEM_PLACE_IN_SECTION("MB_MEM1") uint32_t aOwleyNotifAckBuff[MAX_PARAM_OF_OWLEY_NOTIF_FUNCTIONS];/*shared*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Owley response callbacks: set event to release waiting task
  * @param  ComObj pointer to the Owley com param buffer
  */
static void MBMUXIF_IsrOwleyRespRcvCb(void *ComObj);

/**
  * @brief  Owley notification callbacks: schedules a task in order to quit the ISR
  * @param  ComObj pointer to the Owley com param buffer
  */
static void MBMUXIF_IsrOwleyNotifRcvCb(void *ComObj);

/**
  * @brief  Owley task to process the notification
  */
static void MBMUXIF_TaskOwleyNotifRcv(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
int8_t MBMUXIF_OwleyInit(void)
{
  FEAT_INFO_Param_t *p_cm0plus_system_info;
  int32_t cm0_vers = 0;
  int8_t ret = 0;

  /* USER CODE BEGIN MBMUXIF_OwleyInit */

  /* USER CODE END MBMUXIF_OwleyInit */

  p_cm0plus_system_info = MBMUXIF_SystemGetFeatCapabInfoPtr(FEAT_INFO_SYSTEM_ID);
  /* abstract CM0 release version from RC (release candidate) and compare */
  cm0_vers = p_cm0plus_system_info->Feat_Info_Feature_Version >> APP_VERSION_SUB2_SHIFT;
  if (cm0_vers < (LAST_COMPATIBLE_CM0_RELEASE >> APP_VERSION_SUB2_SHIFT))
  {
    ret = -4; /* version incompatibility */
  }
  if (ret >= 0)
  {
    ret = MBMUX_RegisterFeature(FEAT_INFO_OWLEY_ID, MBMUX_CMD_RESP,
                                MBMUXIF_IsrOwleyRespRcvCb,
                                aOwleyCmdRespBuff, sizeof(aOwleyCmdRespBuff));
  }
  if (ret >= 0)
  {
    ret = MBMUX_RegisterFeature(FEAT_INFO_OWLEY_ID, MBMUX_NOTIF_ACK,
                                MBMUXIF_IsrOwleyNotifRcvCb,
                                aOwleyNotifAckBuff, sizeof(aOwleyNotifAckBuff));
  }
  if (ret >= 0)
  {
    UTIL_SEQ_RegTask(1 << CFG_SEQ_Task_MbOwleyNotifRcv, UTIL_SEQ_RFU, MBMUXIF_TaskOwleyNotifRcv);
  }

  if (ret >= 0)
  {
    ret = MBMUXIF_SystemSendCm0plusRegistrationCmd(FEAT_INFO_OWLEY_ID);
    if (ret < 0)
    {
      ret = -3;
    }
  }

  if (ret >= 0)
  {
    ret = 0;
  }

  /* USER CODE BEGIN MBMUXIF_OwleyInit_Last */

  /* USER CODE END MBMUXIF_OwleyInit_Last */

  return ret;
}

MBMUX_ComParam_t *MBMUXIF_GetOwleyFeatureCmdComPtr(void)
{
  /* USER CODE BEGIN MBMUXIF_GetOwleyFeatureCmdComPtr_1 */

  /* USER CODE END MBMUXIF_GetOwleyFeatureCmdComPtr_1 */
  MBMUX_ComParam_t *com_param_ptr = MBMUX_GetFeatureComPtr(FEAT_INFO_OWLEY_ID, MBMUX_CMD_RESP);
  if (com_param_ptr == NULL)
  {
    Error_Handler(); /* feature isn't registered */
  }
  return com_param_ptr;
  /* USER CODE BEGIN MBMUXIF_GetOwleyFeatureCmdComPtr_Last */

  /* USER CODE END MBMUXIF_GetOwleyFeatureCmdComPtr_Last */
}

void MBMUXIF_OwleySendCmd(void)
{
  /* USER CODE BEGIN MBMUXIF_OwleySendCmd */

  /* USER CODE END MBMUXIF_OwleySendCmd */
  if (MBMUX_CommandSnd(FEAT_INFO_OWLEY_ID) == 0)
  {
    UTIL_SEQ_WaitEvt(1 << CFG_SEQ_Evt_MbOwleyRespRcv);
  }
  else
  {
    Error_Handler();
  }
  /* USER CODE BEGIN MBMUXIF_OwleySendCmd_Last */

  /* USER CODE END MBMUXIF_OwleySendCmd_Last */
}

void MBMUXIF_OwleySendAck(void)
{
  /* USER CODE BEGIN MBMUXIF_OwleySendAck_1 */

  /* USER CODE END MBMUXIF_OwleySendAck_1 */
  if (MBMUX_AcknowledgeSnd(FEAT_INFO_OWLEY_ID) != 0)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN MBMUXIF_OwleySendAck_Last */

  /* USER CODE END MBMUXIF_OwleySendAck_Last */
}

/* USER CODE BEGIN EFD */

/* USER CODE END EFD */

/* Private functions ---------------------------------------------------------*/
static void MBMUXIF_IsrOwleyRespRcvCb(void *ComObj)
{
  /* USER CODE BEGIN MBMUXIF_IsrOwleyRespRcvCb_1 */

  /* USER CODE END MBMUXIF_IsrOwleyRespRcvCb_1 */
  UTIL_SEQ_SetEvt(1 << CFG_SEQ_Evt_MbOwleyRespRcv);
  /* USER CODE BEGIN MBMUXIF_IsrOwleyRespRcvCb_Last */

  /* USER CODE END MBMUXIF_IsrOwleyRespRcvCb_Last */
}

static void MBMUXIF_IsrOwleyNotifRcvCb(void *ComObj)
{
  /* USER CODE BEGIN MBMUXIF_IsrOwleyNotifRcvCb_1 */

  /* USER CODE END MBMUXIF_IsrOwleyNotifRcvCb_1 */
  OwleyComObj = (MBMUX_ComParam_t *) ComObj;
  UTIL_SEQ_SetTask(1 << CFG_SEQ_Task_MbOwleyNotifRcv, CFG_SEQ_Prio_0);
  /* USER CODE BEGIN MBMUXIF_IsrOwleyNotifRcvCb_Last */

  /* USER CODE END MBMUXIF_IsrOwleyNotifRcvCb_Last */
}

static void MBMUXIF_TaskOwleyNotifRcv(void)
{
  /* USER CODE BEGIN MBMUXIF_TaskOwleyNotifRcv_1 */

  /* USER CODE END MBMUXIF_TaskOwleyNotifRcv_1 */
  Process_Owley_Notif(OwleyComObj);
  /* USER CODE BEGIN MBMUXIF_TaskOwleyNotifRcv_Last */

  /* USER CODE END MBMUXIF_TaskOwleyNotifRcv_Last */
}

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */
