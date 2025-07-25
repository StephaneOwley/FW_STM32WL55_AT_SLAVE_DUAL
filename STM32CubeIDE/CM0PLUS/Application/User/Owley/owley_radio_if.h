/*
 * owley_radio_if.h
 *
 *  Created on: Jul 16, 2025
 *      Author: sloiseau
 */
#ifndef OWLEY_RADIO_IF_H
#define OWLEY_RADIO_IF_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @file owley_radio_if.h
 * @brief Interface d'abstraction radio utilisée par la couche Owley.
 *
 * Ce fichier définit l’ensemble des fonctions que tout backend radio
 * (Sigfox, OwMod, LoRa, mock, etc.) doit implémenter pour être utilisé
 * par la couche applicative Owley (owley_comm).
 *
 * Aucune dépendance à la stack Sigfox ne doit remonter dans l’API Owley.
 */


/**
 * @brief Statut de retour standard pour toutes les fonctions radio.
 */
typedef enum {
    RADIO_OK = 0,      /**< Opération réussie */
    RADIO_ERR = -1     /**< Erreur générique */
} RadioStatus_t;


/**
 * @brief Initialise la pile radio pour une région donnée.
 *
 * @param region Numéro de région radio (ex: 1 = RC1, 2 = RC2, 3 = RC3C).
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_init(uint8_t region);

/**
 * @brief Envoie une trame via le canal radio.
 *
 * @param data Pointeur vers les données à envoyer (1 à 12 octets).
 * @param len Longueur du buffer `data`.
 * @param request_downlink true = demande de downlink, false sinon.
 * @param repetitions Nombre de répétitions radio (1 à 3).
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_send(const uint8_t *data, uint8_t len, uint8_t *data_dl, bool request_downlink, uint8_t repetitions);

/**
 * @brief Récupère l'identifiant unique du module radio.
 *
 * @param id Buffer de 4 octets à remplir avec le Device ID.
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_get_id(uint8_t id[4]);

/**
 * @brief Récupère la PAC (clé d'activation) du module radio.
 *
 * @param pac Buffer de 8 octets à remplir avec la PAC.
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_get_pac(uint8_t pac[8]);

/**
 * @brief Démarre une émission continue (CW) sur une fréquence donnée.
 *
 * Cette fonction active une porteuse continue à puissance constante,
 * sans modulation, pour les tests de spectre RF.
 *
 * @param freq_hz Fréquence RF en Hz (ex: 868100000).
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_start_CW(uint32_t freq_hz);

/**
 * @brief Arrête l’émission CW en cours.
 *
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */
RadioStatus_t OwleyRadio_stop_CW(void);

/**
 * @brief ferme la librairie Sifox
 *
 * @return RADIO_OK si succès, RADIO_ERR sinon.
 */

RadioStatus_t OwleyRadio_close(void);


#endif /* OWLEY_RADIO_IF_H */


