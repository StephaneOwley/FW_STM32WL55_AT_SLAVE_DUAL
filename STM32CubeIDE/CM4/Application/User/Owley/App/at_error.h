/*
 * at_error.h
 *
 *  Created on: Jul 18, 2025
 *      Author: sloiseau
 */

#ifndef AT_ERROR_H
#define AT_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* AT_ERROR_H */
