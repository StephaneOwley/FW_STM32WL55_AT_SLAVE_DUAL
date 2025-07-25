/**
  ****************************************************************************
  * @file    owley_comm.h
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

#ifndef OWLEY_COMM_H
#define OWLEY_COMM_H

#include <stdint.h>
#include <stdbool.h>
#include "at_command_owley.h"
#include "owley_radio_if.h"

#define OWLEY_DEBUG 1

/**
 * @file owley_comm.h
 * @brief Interface publique Owley — Couche applicative de communication radio.
 *
 * Cette API abstrait complètement l'accès au backend radio (Sigfox ou autre),
 * et expose un ensemble de fonctions simples pour initialiser la pile,
 * envoyer une trame, ou récupérer les informations du device.
 *
 * Tous les appels retournent 0 en cas de succès, -1 en cas d'échec.
 */


/**
 * @brief Initialise la pile radio Owley pour une région donnée.
 *
 * Cette fonction doit être appelée une fois au démarrage,
 * avant tout envoi ou réception.
 *
 * @param region Région radio (1 = RC1, 2 = RC2, 3 = RC3C, etc.)
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_init(uint8_t region);

/**
 * @brief Envoie une trame radio via le backend Owley.
 *
 * Les données doivent être comprises entre 1 et 12 octets.
 * La fonction permet également d’activer un downlink
 * et de configurer le nombre de répétitions.
 *
 * @param data Tableau d’octets à envoyer.
 * @param len Longueur des données (1 à 12).
 * @param request_downlink true = downlink activé.
 * @param repetitions Nombre de répétitions (1 à 3 typiquement).
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_send(const uint8_t *data, uint8_t len, uint8_t *data_dl, bool request_downlink, uint8_t repetitions);

/**
 * @brief Récupère l’identifiant radio unique du device (ID Sigfox ou équivalent).
 *
 * @param id Tableau de 4 octets à remplir.
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_get_id(uint8_t id[4]);

/**
 * @brief Récupère la clé PAC (Pre-Activation Code) du module.
 *
 * @param pac Tableau de 8 octets à remplir.
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_get_key(uint8_t pac[8]);

/**
 * @brief Démarre un test radio CW (onde continue) sur la fréquence spécifiée.
 *
 * @param freq_hz Fréquence en Hz (ex: 868100000).
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_start_CW(uint32_t freq_hz);

/**
 * @brief Arrête l’émission en mode CW.
 *
 * @return 0 si succès, -1 sinon.
 */
int8_t Owley_stop_CW(void);


/**
 * @brief Fournit la versin de la lib Owley
 *
 */
const char* Owley_get_version(void);

#endif /* OWLEY_COMM_H */
