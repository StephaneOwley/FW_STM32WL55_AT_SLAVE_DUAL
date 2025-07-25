/*
 * owley_mbwrapper.h
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */
#ifndef __OWLEY_MBWRAPPER_H__
#define __OWLEY_MBWRAPPER_H__

#include "stdint.h"
#include "stdbool.h"
#include "owley_config.h" // ou l’endroit où est défini RadioStatus_t

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif /* MAX */

#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif /* MAX */

#define OWLEY_SEND_FRAME_SIZE     ((12 * sizeof(uint8_t)) + (8 * sizeof(uint8_t))) // UL + DL
#define OWLEY_GET_ID_SIZE         (4 * sizeof(uint8_t))   // 4 bytes ID
#define OWLEY_GET_PAC_SIZE        (8 * sizeof(uint8_t))   // 8 bytes PAC
#define OWLEY_CW_SIZE             (sizeof(uint32_t))      // 1 param = fréquence en Hz
#define OWLEY_GET_VERSION_SIZE    (sizeof(uint32_t) + sizeof(uint8_t)) // ptr + length

// Calcul taille finale
#define OWLEY_MBWRAP_SHBUF_SIZE   MAX( \
                                      MAX(OWLEY_SEND_FRAME_SIZE, OWLEY_GET_PAC_SIZE), \
                                      MAX(OWLEY_CW_SIZE, MAX(OWLEY_GET_VERSION_SIZE, OWLEY_GET_ID_SIZE)) \
                                   )




RadioStatus_t OWLEY_API_send_frame(uint8_t *ul_data, uint8_t ul_len,
                                   uint8_t *dl_data, uint8_t request_dl,
                                   uint8_t repetitions);

#ifdef __cplusplus
}
#endif

#endif /* __OWLEY_MBWRAPPER_H__ */
