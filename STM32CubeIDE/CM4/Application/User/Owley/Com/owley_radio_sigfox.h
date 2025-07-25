/*
 * owley_radio_sigfox.h
 *
 *  Created on: Jul 16, 2025
 *      Author: sloiseau
 */

#ifndef OWLEY_RADIO_SIGFOX_H
#define OWLEY_RADIO_SIGFOX_H

//#include "sgfx_at.h"
#include "sigfox_types.h"        // inclusion des types Sigfox

/**
 * @file owley_radio_sigfox.h
 * @brief En-tête interne optionnel pour le backend radio Sigfox.
 *
 * Ce fichier ne fait pas partie de l’interface Owley publique.
 * Il sert à exposer des fonctions ou définitions spécifiques à l’implémentation Sigfox,
 * par exemple pour des tests unitaires, des réglages avancés ou des hooks de debug.
 *
 * À inclure uniquement depuis `owley_radio_sigfox.c` ou des outils internes de validation.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialise le backend Sigfox en mode test (par exemple sans ouvrir la pile).
 *
 * À implémenter si besoin pour injecter des mocks, désactiver la RF, etc.
 *
 * @return 0 si succès, -1 sinon.
 */
int OwleyRadioSigfox_mock_init(void);

/**
 * @brief Active un mode trace ST (si supporté par la version de la lib).
 *
 * Peut être utile en développement pour voir les logs internes Sigfox.
 */
void OwleyRadioSigfox_enable_trace(void);

#ifdef __cplusplus
}
#endif

/**
 * @brief initialisation ouverture stack
 */
static sfx_error_t owley_sigfox_open(void);

#endif /* OWLEY_RADIO_SIGFOX_H */
