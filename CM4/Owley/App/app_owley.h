/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_owley.h
  * @author  OWLEY Team
  * @brief   Header of application of the OWLEY Middleware
   ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 OWLEY
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_SIGFOX_H__
#define __APP_SIGFOX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
#define DEFAULT_RC SFX_RC1
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported Functions Prototypes ---------------------------------------------*/
/**
  * @brief  Init Sigfox Application
  */
void MX_Owley_Init(void);

/**
  * @brief  entry Sigfox Process or scheduling
  */
void MX_Owley_Process(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*__APP_SIGFOX_H__*/
