/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file    owley_comm.c
  * @author  Owley Dev Team
  * @brief   Owley Comm Interface
  ******************************************************************************
  *
  * Copyright 2023 Owley.
  * All rights reserved.
  *
  * NO LICENCE
  *
  ******************************************************************************
  */



/* includes -----------------------------------------------------------*/
#include "owley_comm.h"
//#include "owley_radio_if.h"
//#include "at_command_owley.h"
//#include "owley_internal.h"
//#include "owley_lib_version.h"
#include <stdio.h>

// REF A LIB SIGFOX A SUPRPIMER
// #include "sgfx_at.h"
// #include "owley_trace.h"


/**
 * @brief Initialise la pile radio Owley.
 *
 * Appelle l’implémentation du backend via owley_radio_if.
 */
int8_t Owley_init(uint8_t region)
{
    RadioStatus_t status = OwleyRadio_init(region);
    AT_PRINTF("Init: region = %d, status = %d", region, status);
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Envoie une trame radio encapsulée.
 */
int8_t Owley_send(const uint8_t *data, uint8_t len, uint8_t *data_dl, bool request_downlink, uint8_t repetitions)
{


	if (!data || len == 0 || len > 12) {
        //OWLEY_LOG("Send: invalid parameters (len = %d)", len);
		AT_PRINTF("Send: invalid parameters (len = %d)", len);
        return -1;
    }

    //OWLEY_LOG("Send: len = %d, DL = %d, rep = %d", len, request_downlink, repetitions);
	AT_PRINTF("Send: len = %d, DL = %d, rep = %d", len, request_downlink, repetitions);
    RadioStatus_t status = OwleyRadio_send(data, len, data_dl, request_downlink, repetitions);
    // reception et affichage trame descendente
    if (request_downlink && status == RADIO_OK) {
        char rx_buf[2 * 8 + 1] = {0}; // max 8 octets DL, 2 chars/byte + null terminator
        for (uint8_t i = 0; i < 8; i++) {
            sprintf(&rx_buf[2 * i], "%02X", data_dl[i]);
        }
        AT_PRINTF("+RX=<");
        for (uint8_t i = 0; i < 8; i++) {
        	AT_PRINTF("%02X", data_dl[i]);
            if (i < 7) AT_PRINTF(" ");
        }
        AT_PRINTF(">\r\n");
    }
//
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Récupère l'identifiant radio du module.
 */
int8_t Owley_get_id(uint8_t id[4])
{
    RadioStatus_t status = OwleyRadio_get_id(id);
    AT_PRINTF("Get ID: status = %d", status);
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Récupère la PAC du module.
 */
int8_t Owley_get_key(uint8_t pac[8])
{
    RadioStatus_t status = OwleyRadio_get_pac(pac);
    AT_PRINTF("Get PAC: status = %d", status);
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Démarre le mode CW (Continuous Wave).
 */
int8_t Owley_start_CW(uint32_t freq_hz)
{
	//AT_PRINTF("Start CW: freq = %s Hz", freq_hz);
	//AT_PRINTF("Start CW: freq = %u\r\n", (unsigned int)freq_hz);
    RadioStatus_t status = OwleyRadio_start_CW(freq_hz);
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Arrête le mode CW.
 */
int8_t Owley_stop_CW(void)
{
	AT_PRINTF("Stop CW");
    RadioStatus_t status = OwleyRadio_stop_CW();
    return (status == RADIO_OK) ? 0 : -1;
}

/**
 * @brief Fourni la version de la lib Owley.
 */
const char* Owley_get_version(void)
{
    //return OWLEY_LIB_VERSION;
	return 0;
}
