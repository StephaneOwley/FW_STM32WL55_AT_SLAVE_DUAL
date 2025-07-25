/*
 * owley_radio_sigfox.c
 *
 *  Created on: Jul 16, 2025
 *      Author: sloiseau
 */


//#include "st_sigfox_api.h"
//#include "sgfx_eeprom_if.h"
//#include "radio.h"
#include "owley_radio_if.h"
#include "owley_radio_sigfox.h"
//#include "sigfox_api.h"    // API publique ST Sigfox
//#include "sigfox_types.h"        // inclusion des types Sigfox
//#include "radio_driver.h"
//#include "rf_api.h"

//#include <stddef.h>

// REF A LIB SIGFOX A SUPRPIMER POUR DEBUG
//#include "sgfx_at.h"
//#include "owley_trace.h"

//extern RadioEvents_t RfApiRadioEvents;

/**
 * @file owley_radio_sigfox.c
 * @brief Implémentation Sigfox du backend radio Owley.
 *
 * Ce fichier encapsule les appels à la bibliothèque Sigfox officielle
 * et expose les fonctions requises par l’interface générique owley_radio_if.h.
 */

/**
 * @brief Initialise la stack Sigfox pour une région donnée.
 */
RadioStatus_t OwleyRadio_init(uint8_t region)
{
/*	extern sfx_rc_t SFX_RC1;
	extern sfx_rc_t SFX_RC2;
	extern sfx_rc_t SFX_RC3C;
	extern sfx_rc_t SFX_RC4;

	sfx_rc_t *rc;

	switch (region) {
	    case 1: rc = &SFX_RC1; break;
	    case 2: rc = &SFX_RC2; break;
	    case 3: rc = &SFX_RC3C; break;
	    case 4: rc = &SFX_RC4; break;
	    default: rc = &SFX_RC1; break;
	}

	sfx_error_t err = SIGFOX_API_open(rc);
    return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
*/
	return 0;
}

/**
 * @brief Envoie une trame Sigfox (avec ou sans downlink).
 */
RadioStatus_t OwleyRadio_send(const uint8_t *data, uint8_t len, uint8_t *data_dl, bool request_downlink, uint8_t repetitions)
{
/*	AT_PRINTF("dans OwleyRadio_send/r/n");

	sfx_rc_enum_t sfx_rc;
	sfx_error_t error;

	sfx_rc = E2P_Read_Rc();
	error = owley_sigfox_open(sfx_rc);
	if (error != SFX_ERR_NONE) {
	   return error;
	}

	Radio.Init(&RfApiRadioEvents);
	//
	sfx_error_t err = SIGFOX_API_send_frame((uint8_t *)data, len, (uint8_t *)data_dl, repetitions, request_downlink);
	AT_PRINTF("OwleyRadio_send Err: %d", err);

	SIGFOX_API_close();

	return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
*/
	return 0;
}

/**
 * @brief Récupère l'identifiant unique du module Sigfox.
 */
RadioStatus_t OwleyRadio_get_id(uint8_t id[4])
{
/*    sfx_error_t err = SIGFOX_API_get_device_id(id);
    return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
*/
	return 0;

}

/**
 * @brief Récupère la PAC (clé d'activation Sigfox) du module.
 */
RadioStatus_t OwleyRadio_get_pac(uint8_t pac[8])
{
    //sfx_error_t err = SIGFOX_API_get_initial_pac(pac);
    //return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
	return 0;
}

/**
 * @brief Démarre une émission CW (Continuous Wave).
 */
RadioStatus_t OwleyRadio_start_CW(uint32_t freq_hz)
{
	//AT_PRINTF("IN OwleyRadio, Freq = %s\r\n", freq_hz);
	//AT_PRINTF("Start CW by Owley Radio: freq = %u\r\n", (unsigned int)freq_hz);
	//Radio.Init(&RfApiRadioEvents);
	//Radio.SetChannel(freq_hz);           // 5
	//int8_t power = E2P_Read_Power(E2P_Read_Rc());  // 6
	// CW :
	//Radio.SetTxContinuousWave(freq_hz, power, 10);               // 8
	//return 0;

	/*sfx_rc_enum_t sfx_rc;
	sfx_error_t error;

	sfx_rc = E2P_Read_Rc();
	error = owley_sigfox_open(sfx_rc);
	if (error != SFX_ERR_NONE) {
	   return error;
	}

	Radio.Init(&RfApiRadioEvents);
	Radio.SetChannel(freq_hz);
	sfx_error_t err = RF_API_start_continuous_transmission(0);
	return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
	*/
	return 0;
}

/**
 * @brief Arrête l’émission CW.
 */
RadioStatus_t OwleyRadio_stop_CW(void)
{
    //sfx_error_t err = RF_API_stop_continuous_transmission();
	//SIGFOX_API_close();
    //return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
	return 0;
}

/**
 * @brief Ferme la librairie Sigfox
 */
RadioStatus_t OwleyRadio_close(void)
{
	//sfx_error_t err = SIGFOX_API_close();
    //return (err == SFX_ERR_NONE) ? RADIO_OK : RADIO_ERR;
	return 0;
}

/**
 * @brief initialisation ouverture stack
 */
static sfx_error_t owley_sigfox_open(void)
{
  /* USER CODE BEGIN st_sigfox_open_1 */

  /* USER CODE END st_sigfox_open_1 */
  /*sfx_u32 config_words[3] = {0};

  E2P_Read_ConfigWords(sfx_rc, config_words);

  sfx_error_t error = SFX_ERR_NONE;

  //record RCZ
  switch (sfx_rc)
  {
    case SFX_RC1:
    {
      sfx_rc_t SgfxRc = RC1;
      error = SIGFOX_API_open(&SgfxRc);

      break;
    }
    case SFX_RC2:
    {
      sfx_rc_t SgfxRc = RC2;

      error = SIGFOX_API_open(&SgfxRc);

      if (error == SFX_ERR_NONE)
      {
        error = SIGFOX_API_set_std_config(config_words, RC2_SET_STD_TIMER_ENABLE);
      }

      break;
    }
    case SFX_RC3A:
    {
      sfx_rc_t SgfxRc = RC3A;

      error = SIGFOX_API_open(&SgfxRc);

      if (error == SFX_ERR_NONE)
      {
        error = SIGFOX_API_set_std_config(config_words, NA);
      }
      break;
    }
    case SFX_RC3C:
    {
      sfx_rc_t SgfxRc = RC3C;

      error = SIGFOX_API_open(&SgfxRc);

      if (error == SFX_ERR_NONE)
      {
        error = SIGFOX_API_set_std_config(config_words, NA);
      }
      break;
    }
    case SFX_RC4:
    {
      sfx_rc_t SgfxRc = RC4;

      error = SIGFOX_API_open(&SgfxRc);

      if (error == SFX_ERR_NONE)
      {
        error = SIGFOX_API_set_std_config(config_words, RC4_SET_STD_TIMER_ENABLE);
      }
      break;
    }
    case SFX_RC5:
    {
      sfx_rc_t SgfxRc = RC5;

      error = SIGFOX_API_open(&SgfxRc);

      if (error == SFX_ERR_NONE)
      {
        error = SIGFOX_API_set_std_config(config_words, NA);
      }
      break;
    }
    case SFX_RC6:
    {
      sfx_rc_t SgfxRc = RC6;
      error = SIGFOX_API_open(&SgfxRc);
      break;
    }
    case SFX_RC7:
    {
      sfx_rc_t SgfxRc = RC7;
      error = SIGFOX_API_open(&SgfxRc);
      break;
    }
    */
    /* USER CODE BEGIN st_sigfox_open_case */

    /* USER CODE END st_sigfox_open_case */
    /*default:
    {
      error = SFX_ERR_API_OPEN;
      break;
    }
  }

  return error;
  */
  /* USER CODE BEGIN st_sigfox_open_2 */

  /* USER CODE END st_sigfox_open_2 */
	return 0;
}

