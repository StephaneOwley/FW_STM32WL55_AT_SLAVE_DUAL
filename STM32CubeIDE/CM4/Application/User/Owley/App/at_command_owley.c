/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    at_command_owley.c
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


#include "at_command_owley.h"
#include "owley_mbwrapper.h"
#include "owley_utils.h"
#include "stm32wlxx.h"
#include "stm32_tiny_sscanf.h"

/*ATEerror_t AT_return_ok(const char *param)
{
  return AT_OK;
}

ATEerror_t AT_return_error(const char *param)
{
  return AT_ERROR;
}*/


ATEerror_t AT_OwleySend(const char *param)
{

	AT_PRINTF("param brut = %s\r\n", param);


    uint8_t ul_msg[12] = {0};  // Max 12 bytes payload
    uint8_t dl_msg[8] = {0};   // Optionnel
    uint32_t dlFlag = 0;
    uint32_t ul_size = 0;
    uint32_t txRepeat = 1;
    uint32_t nbParam;

    //if (string_To_Data(param, ul_msg, &ul_size) != SUCCESS)
    if (string_To_Data(param, ul_msg, &ul_size) != SUCCESS)
    {
        return AT_PARAM_ERROR;
    }

    if (param[2 * ul_size] == ',')
    {
        nbParam = tiny_sscanf(&param[2 * ul_size + 1], "%u,%u", &dlFlag, &txRepeat);
        if (nbParam > 2)
        {
            return AT_PARAM_ERROR;
        }
    }
    // Envoi Message owley
    RadioStatus_t status = OWLEY_API_send_frame(ul_msg, ul_size, dl_msg, dlFlag, txRepeat);
    // reception et affichage trame descendente
    if (dlFlag && status == RADIO_OK) {
        char rx_buf[2 * 8 + 1] = {0}; // max 8 octets DL, 2 chars/byte + null terminator
        for (uint8_t i = 0; i < 8; i++) {
            sprintf(&rx_buf[2 * i], "%02X", dl_msg[i]);
        }
        AT_PRINTF("+RX=<");
        for (uint8_t i = 0; i < 8; i++) {
        	AT_PRINTF("%02X", dl_msg[i]);
            if (i < 7) AT_PRINTF(" ");
        }
        AT_PRINTF(">\r\n");
    }
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief AT+OWID?
 */
ATEerror_t AT_OwleyGetID(const char *param)
{
    uint8_t id[4];

    //RadioStatus_t status = OwleyRadio_get_id(id);
    if (OwleyRadio_get_id(id) != 0) return AT_ERROR;

    for (int32_t i = OWLEY_ID_MAX_LEN; i > 0; i--)
      {
        AT_PRINTF("%02X", id[i - 1]);
      }
      AT_PRINTF("\r\n");
      return AT_OK;
}

/**
 * @brief AT+OWKEY?
 */
ATEerror_t AT_OwleyGetPAC(const char *param)
{
    uint8_t pac[8];
    //if (Owley_get_key(pac) != 0) return AT_ERROR;
    if (OwleyRadio_get_pac(pac) != 0) return AT_ERROR;
    char out[17] = {0};
    Owley_bytes_to_hex(pac, 8, out);
    AT_PRINTF("%s\r\n", out);
    return AT_OK;
}

/**
 * @brief AT$CW=<freq>
 * 0 → stop
 * 868100000 ou 868.1 → start CW
 */
ATEerror_t AT_OwleyCW(const char *param)
{
/*    if (param == NULL || strlen(param) == 0) return AT_PARAM_ERROR;

    uint32_t freq = 0;
    if (strcmp(param, "0") == 0) {
        if (Owley_stop_CW() != 0) return AT_ERROR;
        return AT_OK;
    }

    if (!Owley_parse_frequency(param, &freq)) return AT_PARAM_ERROR;

    if (Owley_start_CW(freq) != 0)
        return AT_ERROR;

    return AT_OK;*/
	//AT_PRINTF("IN DA LOOP, Freq = %s\r\n", param);

	 uint32_t freq = 0;

	  if (tiny_sscanf(param, "%u", &freq) > 1)
	  {
	    return AT_PARAM_ERROR;
	  }

	  //AT_PRINTF("IN DA LOOP, Freq = %s\r\n", freq);
	  //AT_PRINTF("IN DA LOOP, Freq = %u\r\n", (unsigned int)freq);
	  //AT_PRINTF("IN DA LOOP2, Freq = %u\r\n", (unsigned int)freq);

	  if (freq == 0)
	  {
		  //Owley_stop_CW();
		  OwleyRadio_stop_CW();
	  }
	  else if ((freq > ((uint32_t) 100e6)) && (freq < ((uint32_t) 1e9)))
	  {
	    if (OwleyRadio_start_CW(freq) != 0)
	    {
	      return AT_PARAM_ERROR;
	    }
	  }
	  else if ((freq >  100) && (freq <  1000))
	  {
	    /* user meant Mega... */
	    if (OwleyRadio_start_CW(freq * 1000000) != 0)
	    {
	      return AT_PARAM_ERROR;
	    }
	  }
	  else
	  {
	    return AT_PARAM_ERROR;
	  }

	  return AT_OK;

}

/**
 * @brief AT+OWVER?
 * Fournit la version de la lib
 */
ATEerror_t AT_OwleyGetVersion(const char *param)
{
    const char *version = OWLEY_LIB_VERSION;
    AT_PRINTF("%s\r\n", version);
    return AT_OK;
}
