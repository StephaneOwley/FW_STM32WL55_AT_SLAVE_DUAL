/*
 * mbmuxif_owley.c
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */

#include "mbmuxif_owley.h"


MBMUX_ComParam_t aOwleyCmdRespBuff;
MBMUX_ComParam_t aOwleyNotifAckBuff;

void MBMUXIF_SetOwleyFeatureCallback(void (*MsgCb)(MBMUX_ComParam_t *ComObj))
{
  MBMUX_SetFeatureCallback(FEAT_INFO_OWLEY_ID, MsgCb);
}



int MBMUXIF_OwleyInit(void)
{
    return MBMUX_RegisterFeatureCallback(FEAT_INFO_OWLEY_ID, OWLEY_CmdHandler);
}
