/*
 * owley_mbwrapper.c
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */


void MBMUX_OWLEYCommandReceived(MBMUX_ComParam_t *com_obj)
{
  uint32_t *com_buf = com_obj->ParamBuf;

  uint8_t *data_ul         = (uint8_t *) com_buf[0];
  uint8_t  len             = (uint8_t) com_buf[1];
  uint8_t *data_dl         = (uint8_t *) com_buf[2];
  bool     request_dl      = (bool)    com_buf[3];
  uint8_t  repetitions     = (uint8_t) com_buf[4];

  RadioStatus_t status = OwleyRadio_send(data_ul, len, data_dl, request_dl, repetitions);

  com_obj->ReturnVal = (uint32_t) status;

  MBMUX_AcknowledgeSndCmd();  // Ou équivalent pour signaler fin traitement
}

/*void OWLEY_CmdHandler(void)
{
    switch (aOwleyCmdRespBuff.MsgId)
    {
        case OWLEY_SEND_FRAME_ID:
            OWLEY_IF_SendFrame(&aOwleyCmdRespBuff.ParamBuf[1],
                               aOwleyCmdRespBuff.ParamBuf[0]);
            aOwleyCmdRespBuff.ParamBuf[0] = 0x00; // succès
            aOwleyCmdRespBuff.ParamCnt = 1;
            MBMUX_ResponseSnd(FEAT_INFO_OWLEY_ID);
            break;

        default:
            aOwleyCmdRespBuff.ParamBuf[0] = 0xFE; // erreur
            MBMUX_ResponseSnd(FEAT_INFO_OWLEY_ID);
            break;
    }
}*/
