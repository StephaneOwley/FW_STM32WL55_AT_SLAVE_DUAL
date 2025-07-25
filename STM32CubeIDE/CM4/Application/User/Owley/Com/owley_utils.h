/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    at_utils_owley.h
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

#ifndef OWLEY_UTILS_H
#define OWLEY_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "owley_config.h"

/**
 * @brief Convertit une chaîne hexadécimale ASCII en tableau de données binaires.
 * @see owley_internal.c pour détails et codes retour.
 */
int string_To_Data(const char *str, uint8_t *data, uint32_t *dataSize);

/**
 * @brief Convertit un tableau binaire en chaîne hexadécimale terminée par '\0'.
 *
 * @param input Données binaires à convertir.
 * @param len Nombre d'octets à convertir.
 * @param output Chaîne de sortie (taille minimale : 2*len + 1).
 */
void Owley_bytes_to_hex(const uint8_t *input, uint8_t len, char *output);

/**
 * @brief Affiche dans les logs un buffer binaire formaté en hex, avec libellé.
 *
 * @param label Texte à afficher avant le buffer.
 * @param data Données binaires à afficher.
 * @param len Longueur du tableau data.
 */
void Owley_log_buffer(const char *label, const uint8_t *data, uint8_t len);

/**
 * @brief Parse une fréquence en texte (ex: "868.1" ou "868100000") en Hz.
 *
 * Accepte les formats :
 * - MHz avec point (ex: "868.1") → renvoie 868100000
 * - Hz entier (ex: "868100000") → renvoie 868100000
 *
 * @param input Chaîne à parser.
 * @param freq_hz Résultat (en Hz) si succès.
 * @return true si parsing OK, false sinon.
 */
bool Owley_parse_frequency(const char *input, uint32_t *freq_hz);

#endif /* OWLEY_UTILS_H */
