/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sigfox_mbwrapper.h
  * @author  MCD Application Team
  * @brief   This file implements the CM0 side wrapper of the SigfoxMac interface
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIGFOX_MBWRAPPER_CM4_H__
#define __SIGFOX_MBWRAPPER_CM4_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mbmux_table.h"
#include "sigfox_types.h"
#include "sigfox_api.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/*!
  * Sigfox callback structure
*/
typedef struct sOwleyCallback
{
  /*!
  * \brief   Measures the battery level
  *
  * \retval  Battery level [0: node is connected to an external
  *          power source, 1..254: battery level, where 1 is the minimum
  *          and 254 is the maximum value, 255: the node was not able
  *          to measure the battery level]
  */
  uint16_t (*GetBatteryLevel)(void);
  /*!
  * \brief   Measures the temperature level
  *
  * \retval  Temperature level
  */
  int16_t (*GetTemperatureLevel)(void);
} OwleyCallback_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief This function processes the callbacks and primitives from Cm0
  * @param ComObj exchange buffer parameter
  */
void Process_Owley_Notif(MBMUX_ComParam_t *ComObj);

/**
  * @brief Register the callbacks structure for the process notification
  * @param SigfoxCallback struct of callbacks
  */
void Owley_Register(OwleyCallback_t *OwleyCallback);

//
sfx_error_t OWLEY_API_open(sfx_rc_t *rc);


/*!******************************************************************
 * \fn sfx_error_t OWLEY_API_start_loc_transmission(sfx_u32 frequency, sfx_u32 power);
 * \brief Executes an Conituous Owley Geolocation Frame Emission
 *        SIGFOX_API_stop_continuous_transmission has to be called to stop the continuous transmission.
 *
 * \param[in] sfx_u32 frequency                Frequency at which the signal has to be generated
 * \param[in] sfx_u32 power                    Frame Tx Output Power (dBm)
 *
 * \retval  The sfx_error_t is composed of the following :
 *
 *    MSB_____________________________________________LSB
 *    15                      8|7                     0
 *     |                       |                      |
 *     |   MANUF_ERROR_CODE    |  SIGFOX_ERROR_CODE   |
 *     |_______________________|______________________|
 *
 *  SIGFOX_ERROR_CODE for this function : XX
 *******************************************************************/
sfx_error_t OWLEY_API_start_loc_transmission(sfx_u32 frequency, sfx_u32 power);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*__SIGFOX_MBWRAPPER_CM4_H__ */
