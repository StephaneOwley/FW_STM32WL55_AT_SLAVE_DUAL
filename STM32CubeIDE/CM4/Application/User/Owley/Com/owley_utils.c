/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    owley_utils.c
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

#include "owley_utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stm32wlxx.h>
#include <stm32_tiny_sscanf.h>


static int is_Hex(char Char)
{
  if (((Char >= '0') && (Char <= '9')) ||
      ((Char >= 'a') && (Char <= 'f')) ||
      ((Char >= 'A') && (Char <= 'F')))
  {
    return SUCCESS;
  }
  else
  {
    return ERROR;
  }
}

int string_To_Data(const char *str, uint8_t *data, uint32_t *dataSize)
{
  /* USER CODE BEGIN stringToData_1 */

  /* USER CODE END stringToData_1 */
  uint8_t ii = 0;
  char hex[3];
  hex[2] = 0;
  while ((*str != '\0') && (*str != ','))
  {
    hex[0] = *str++;
    hex[1] = *str++;

    /*check if input is hex */
    if ((is_Hex(hex[0]) == ERROR) || (is_Hex(hex[1]) == ERROR))
    {
      return ERROR;
    }
    /*check if input is even nb of character*/
    if ((hex[1] == '\0') || (hex[1] == ','))
    {
      return ERROR;
    }
    if (tiny_sscanf(hex, "%hhx", &data[ii]) != 1)
    {
      return ERROR;
    }
    ii++;
    if (ii > OWLEY_UL_PAYLOAD_MAX_LEN)
    {
      return ERROR;
    }
  }
  *dataSize = ii;
  if (ii == 0)
  {
    return ERROR;
  }
  return SUCCESS;
  /* USER CODE BEGIN stringToData_2 */

  /* USER CODE END stringToData_2 */
}

/**
 * @brief Convertit un buffer binaire en chaîne hex.
 */
void Owley_bytes_to_hex(const uint8_t *input, uint8_t len, char *output)
{
    static const char hex[] = "0123456789ABCDEF";
    for (uint8_t i = 0; i < len; i++) {
        output[2 * i]     = hex[(input[i] >> 4) & 0x0F];
        output[2 * i + 1] = hex[input[i] & 0x0F];
    }
    output[2 * len] = '\0';
}

/**
 * @brief Affiche un buffer hexadécimal avec libellé.
 */
void Owley_log_buffer(const char *label, const uint8_t *data, uint8_t len)
{
    char hex_str[2 * 12 + 1] = {0}; // max 12 octets Sigfox
    if (len > 12) len = 12;

    Owley_bytes_to_hex(data, len, hex_str);
    //OWLEY_LOG("%s [%s]", label, hex_str);
}

/**
 * @brief Parse une fréquence "868100000" ou "868.1" en Hz.
 */
bool Owley_parse_frequency(const char *input, uint32_t *freq_hz)
{
    if (!input || !freq_hz) return false;

    if (strchr(input, '.')) {
        // Format avec point → MHz
        double mhz = atof(input);
        if (mhz < 100.0 || mhz > 1000.0) return false;
        *freq_hz = (uint32_t)(mhz * 1000000.0);
        return true;
    } else {
        // Format entier → Hz
        char *end = NULL;
        long val = strtol(input, &end, 10);
        if (*end != '\0' || val <= 100000000 || val > 1000000000) return false;
        *freq_hz = (uint32_t)val;
        return true;
    }
}
