/*
 * mbmuxif_owley.c
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */

#include "mbmuxif_owley.h"

MBMUX_ComParam_t aOwleyCmdRespBuff;
MBMUX_ComParam_t aOwleyNotifAckBuff;

MBMUX_ComParam_t *MBMUXIF_GetOwleyFeatureCmdComPtr(void)
{
  /* USER CODE BEGIN MBMUXIF_GetOwleyFeatureCmdComPtr_1 */

  /* USER CODE END MBMUXIF_GetOwleyFeatureCmdComPtr_1 */
  MBMUX_ComParam_t *com_param_ptr = MBMUX_GetFeatureComPtr(OWLEY_SEND_FRAME_ID, MBMUX_CMD_RESP);
  if (com_param_ptr == NULL)
  {
    Error_Handler(); /* feature isn't registered */
  }
  return com_param_ptr;
  /* USER CODE BEGIN MBMUXIF_GetSigfoxFeatureCmdComPtr_Last */

  /* USER CODE END MBMUXIF_GetSigfoxFeatureCmdComPtr_Last */
}


// init par ChatGPT
int MBMUXIF_OwleyInit(void)
{
    return MBMUX_InitFeature(FEAT_INFO_OWLEY_ID,
                              &aOwleyCmdRespBuff,
                              &aOwleyNotifAckBuff,
                              MBMUX_NOTIF_RSP,
                              NULL); // Pas de callback local
}

MBMUX_ComParam_t* MBMUXIF_GetOwleyCmdRespBuffer(void)
{
    return &aOwleyCmdRespBuff;
}
