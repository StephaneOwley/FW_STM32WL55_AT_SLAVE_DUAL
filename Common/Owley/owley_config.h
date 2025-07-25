/*
 * owley_config.h
 *
 *  Created on: Jul 23, 2025
 *      Author: sloiseau
 */

#ifndef __OWLEY_CONFIG_H
#define __OWLEY_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* ----------------------- MBMUX Feature ID & Msg IDs ------------------------ */
/* --------------------------------------------------------------------------- */

#define OWLEY_CMD_PARAM_MAX_NB           5 //Nombre max de paramètres dans une commande MBMUX


typedef enum
{
  /* CmdResp */
  OWLEY_SEND_FRAME_ID = 0,
  OWLEY_START_CW_ID,
  OWLEY_STOP_CW_ID,
  OWLEY_GET_VERSION_ID,
  OWLEY_GET_DEVICE_ID,
  /* USER CODE BEGIN Owley_MsgIdTypeDef */

  /* USER CODE END Owley_MsgIdTypeDef */

  OWLEY_MSGID_LAST  // nombre total d’IDs
} Owley_MsgIdTypeDef;

/* --------------------------------------------------------------------------- */
/* -------------------------- Taille des buffers Owley ----------------------- */
/* --------------------------------------------------------------------------- */

#define OWLEY_UL_PAYLOAD_MAX_LEN 12
#define OWLEY_DL_PAYLOAD_MAX_LEN 8
#define OWLEY_ID_MAX_LEN 4

/* --------------------------------------------------------------------------- */
/* ----------------------- Types de retour personnalisés --------------------- */
/* --------------------------------------------------------------------------- */

#define OWLEY_OK                      0
#define OWLEY_ERROR_UNKNOWN_COMMAND   0xFFFF

#ifdef __cplusplus
}
#endif




#endif // __OWLEY_CONFIG_H
