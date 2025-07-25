/*
 * owley_mbwrapper.c
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */

#include "owley_mbwrapper.h"
#include "mbmuxif_owley.h"

// @brief Sigfox buffer to exchange data between from CM4 to CM0+
UTIL_MEM_PLACE_IN_SECTION("MB_MEM1") uint8_t aOwleyMbWrapShareBuffer[OWLEY_MBWRAP_SHBUF_SIZE];



RadioStatus_t OWLEY_API_send_frame(uint8_t *ul_data, uint8_t ul_len,
                                   uint8_t *dl_data, uint8_t request_dl,
                                   uint8_t repetitions)

{
  if (ul_data == NULL) return 1;
  if (dl_data == NULL) return 2;

  // 1. Copier dans RAM partagée
  UTIL_MEM_cpy_8(aOwleyMbWrapShareBuffer, ul_data, OWLEY_UL_PAYLOAD_MAX_LEN);
  UTIL_MEM_cpy_8(aOwleyMbWrapShareBuffer + OWLEY_UL_PAYLOAD_MAX_LEN, dl_data, OWLEY_DL_PAYLOAD_MAX_LEN);

  // 2. Créer objet MBMUX
  MBMUX_ComParam_t *com_obj = MBMUXIF_GetOwleyFeatureCmdComPtr();
  uint32_t *com_buf = com_obj->ParamBuf;
  uint16_t i = 0;

  com_obj->MsgId = OWLEY_SEND_FRAME_ID;

  com_buf[i++] = (uint32_t) aOwleyMbWrapShareBuffer;                                  // ul_data
  com_buf[i++] = (uint32_t) ul_len;                                                   // taille
  com_buf[i++] = (uint32_t)(aOwleyMbWrapShareBuffer + OWLEY_UL_PAYLOAD_SIZE);         // dl_data
  com_buf[i++] = (uint32_t) tx_mode;
  com_buf[i++] = (uint32_t) request_downlink;

  com_obj->ParamCnt = i;

  // 3. Appel réel
  MBMUXIF_OwleySendCmd();

  // 4. Copier retour
  UTIL_MEM_cpy_8(ul_data, aOwleyMbWrapShareBuffer, OWLEY_UL_PAYLOAD_SIZE);
  UTIL_MEM_cpy_8(dl_data, aOwleyMbWrapShareBuffer + OWLEY_UL_PAYLOAD_SIZE, OWLEY_DL_PAYLOAD_SIZE);

  return (sfx_error_t) com_obj->ReturnVal;
}

