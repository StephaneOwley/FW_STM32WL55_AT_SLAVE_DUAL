/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    at_command_owley.h
  * @author  OWLEY dev Team
  * @brief   Owley AT command App Middleware
  ******************************************************************************
  * @attention
  *
  * Copyright  Owley.
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef AT_COMMAND_OWLEY_H
#define AT_COMMAND_OWLEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32_adv_trace.h"
#include <stdint.h>    // pour uint8_t, etc.
//#include "at_error.h"
//#include "owley_trace.h"  // pour AT_PRINTF / AT_PPRINTF


/**
  * @brief  Return values for AT command processing
  */
typedef enum eATEerror
{
  AT_OK = 0,
  AT_ERROR,
  AT_PARAM_ERROR,
  AT_BUSY_ERROR,
  AT_TEST_PARAM_OVERFLOW,
  AT_LIB_ERROR,
  AT_TX_TIMEOUT, /*CS Channel Busy*/
  AT_RX_TIMEOUT,
  AT_RX_ERROR,
  AT_RECONF_ERROR,
  AT_MAX,
} ATEerror_t;

/* AT printf */
#define AT_PRINTF(...)     do{  UTIL_ADV_TRACE_COND_FSend(VLEVEL_OFF, T_REG_OFF, TS_OFF, __VA_ARGS__);}while(0)
#define AT_PPRINTF(...)    do{ } while( UTIL_ADV_TRACE_OK \
                               != UTIL_ADV_TRACE_COND_FSend(VLEVEL_ALWAYS, T_REG_OFF, TS_OFF, __VA_ARGS__) ) // Polling Mode


/**
  * @brief  Return AT_OK in all cases
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
//ATEerror_t AT_return_ok(const char *param);
//ATEerror_t AT_return_error(const char *param);
ATEerror_t AT_OwleySend(const char *param);
ATEerror_t AT_OwleyGetID(const char *param);
ATEerror_t AT_OwleyGetPAC(const char *param);
ATEerror_t AT_OwleyCW(const char *param);
ATEerror_t AT_OwleyGetVersion(const char *param);

#endif /* AT_CMD_OWLEY_H */
