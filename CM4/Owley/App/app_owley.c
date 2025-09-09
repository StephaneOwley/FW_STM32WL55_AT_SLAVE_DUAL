/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_owley.c
  * @author  Owley Team
  * @brief   Application of the OWLEY Middleware
  ******************************************************************************
  * @attention
  *
  * Copyright (c) OWLEY
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_owley.h"
#include "owley_app.h"
#include "sys_app.h"
#include "stm32_seq.h"


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
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
void MX_Owley_Init(void)
{
  /* USER CODE BEGIN MX_Sigfox_Init_1 */

  /* USER CODE END MX_Sigfox_Init_1 */
  SystemApp_Init();
  /* USER CODE BEGIN MX_Sigfox_Init_1_1 */

  /* USER CODE END MX_Sigfox_Init_1_1 */
  Owley_Init();
  /* USER CODE BEGIN MX_Sigfox_Init_2 */

  /* USER CODE END MX_Sigfox_Init_2 */
}

void MX_Owley_Process(void)
{
  /* USER CODE BEGIN MX_Sigfox_Process_1 */

  /* USER CODE END MX_Sigfox_Process_1 */
  UTIL_SEQ_Run(UTIL_SEQ_DEFAULT);
  /* USER CODE BEGIN MX_Sigfox_Process_2 */

  /* USER CODE END MX_Sigfox_Process_2 */
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private Functions Definition -----------------------------------------------*/

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */
