/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    kms_platf_objects_config.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for Key Management Services (KMS)
  *          module platform objects management configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef KMS_PLATF_OBJECTS_CONFIG_H
#define KMS_PLATF_OBJECTS_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "kms_platf_objects_interface.h"
/* USER CODE BEGIN KMS_PLATF_OBJECTS_CONFIG_Includes */
#include "stm32wlxx.h"
#include "app_sigfox.h"  /* SIGFOX_KMS */
#include "st_sigfox_api.h"
#include "sgfx_credentials.h"
#include "sigfox_data.h"
/* USER CODE END KMS_PLATF_OBJECTS_CONFIG_Includes */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Key_Management_Services Key Management Services (KMS)
  * @{
  */

/** @addtogroup KMS_PLATF Platform Objects
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN KMS_PLATF_OBJECTS_CONFIG_Exported_Constants */

/** @addtogroup KMS_PLATF_Exported_Constants Exported Constants
  * @note KMS support different type of objects, their respective ranges are
  *       defined here
  * @{
  */

/* We consider that the ORDER (static = lower ids) will be kept  */
#define KMS_INDEX_MIN_EMBEDDED_OBJECTS                1UL   /*!< Embedded objects min ID. Must be > 0 as '0' is never a
                                                                 valid key index */
#define KMS_INDEX_MAX_EMBEDDED_OBJECTS               29UL   /*!< Embedded objects max ID */
#define KMS_INDEX_MIN_NVM_STATIC_OBJECTS             30UL   /*!< NVM static objects min ID */
#define KMS_INDEX_MAX_NVM_STATIC_OBJECTS             49UL   /*!< NVM static objects max ID */
#define KMS_INDEX_MIN_NVM_DYNAMIC_OBJECTS            50UL   /*!< NVM dynamic objects min ID */
#define KMS_INDEX_MAX_NVM_DYNAMIC_OBJECTS            69UL   /*!< NVM dynamic objects max ID */

#define KMS_INDEX_MIN_VM_DYNAMIC_OBJECTS             50UL   /*!< VM dynamic objects min ID */
#define KMS_INDEX_MAX_VM_DYNAMIC_OBJECTS             69UL   /*!< VM dynamic objects max ID */

/* When EXTERNAL TOKEN is not supported the below values can be commented */
#define KMS_INDEX_MIN_EXT_TOKEN_STATIC_OBJECTS        70UL  /*!< External token static objects min ID */
#define KMS_INDEX_MAX_EXT_TOKEN_STATIC_OBJECTS        89UL  /*!< External token static objects max ID */
#define KMS_INDEX_MIN_EXT_TOKEN_DYNAMIC_OBJECTS       90UL  /*!< External token dynamic objects min ID */
#define KMS_INDEX_MAX_EXT_TOKEN_DYNAMIC_OBJECTS      110UL  /*!< External token dynamic objects max ID */

/* Blob import key index */
#define KMS_INDEX_BLOBIMPORT_VERIFY       (1U)      /*!< Index in @ref KMS_PlatfObjects_EmbeddedList
                                                         where the blob verification key is stored */
#define KMS_INDEX_BLOBIMPORT_DECRYPT      (2U)      /*!< Index in @ref KMS_PlatfObjects_EmbeddedList
                                                         where the blob decryption key is stored */

#define RAW_TO_4X_INT32A_KMS(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
  0x##a##b##c##d, 0x##e##f##g##h, 0x##i##j##k##l, 0x##m##n##o##p
#define RAW_TO_2X_INT32A_KMS(a,b,c,d,e,f,g,h)\
  0x##a##b##c##d, 0x##e##f##g##h
#define RAW_TO_1X_INT32A_KMS(a,b,c,d)\
  0x##d##c##b##a

#define FORMAT_KMS_KEY(...) RAW_TO_4X_INT32A_KMS(__VA_ARGS__)
#define FORMAT_KMS_PAC(...) RAW_TO_2X_INT32A_KMS(__VA_ARGS__)
#define FORMAT_KMS_ID(...) RAW_TO_1X_INT32A_KMS(__VA_ARGS__)
/**
  * @}
  */

/* USER CODE END KMS_PLATF_OBJECTS_CONFIG_Exported_Constants */

/*
 * Embedded objects definition
 *
 */
#ifdef KMS_PLATF_OBJECTS_C
/* USER CODE BEGIN KMS_PLATF_OBJECTS_CONFIG_Embedded_Objects_Definition */
/* Place code in a specific section*/

#if defined(__ICCARM__)
#pragma default_variable_attributes = @ ".USER_embedded_Keys"
#elif defined(__CC_ARM)
#pragma arm section rodata = ".USER_embedded_Keys"
#endif

KMS_DECLARE_BLOB_STRUCT(, 32);

#if defined(__GNUC__)
#pragma GCC push_options
#pragma GCC optimize ("O0")
__attribute__((section(".USER_embedded_Keys")))
#endif
/* These objects are used by user tKMS application                 */
static const kms_obj_keyhead_32_t   Sigfox_Data_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  128,                             /*  uint32_t blobs_size; */
  9,                               /*  uint32_t blobs_count; */
  1,                               /*  uint32_t object_id; */
  {
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        MANUF_SIGNATURE_LENGTH,  FORMAT_KMS_KEY(SIGFOX_KEY),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_TOKEN,        sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_LABEL,        12,                      0x58464753U, 0x50595243U, 0x00383231U      /* 'SGFX', 'CRYP', '128' */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_32_t   Sigfox_pac =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  128,                             /*  uint32_t blobs_size; */
  9,                               /*  uint32_t blobs_count; */
  2,                               /*  uint32_t object_id; */
  {
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        MANUF_PAC_LENGTH,        FORMAT_KMS_PAC(SIGFOX_PAC),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_TOKEN,        sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_LABEL,        12,                      0x58464753U, 0x434150U, 0x00383231U,      /* 'SGFX', 'PAC', '128' */
    0UL, 0UL /* Fill end of table */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_32_t   Sigfox_id =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  128,                             /*  uint32_t blobs_size; */
  9,                               /*  uint32_t blobs_count; */
  3,                               /*  uint32_t object_id; */
  {
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        MANUF_DEVICE_ID_LENGTH,  FORMAT_KMS_ID(SIGFOX_ID),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_TOKEN,        sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_LABEL,        12,                      0x58464753U, 0x4449U, 0x00383231U,      /* 'SGFX', 'ID', '128' */
    0UL, 0UL, 0UL /* Fill end of table */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_32_t   Sigfox_Public_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  128,                             /*  uint32_t blobs_size; */
  9,                               /*  uint32_t blobs_count; */
  4,                               /*  uint32_t object_id; */
  {
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        MANUF_SIGNATURE_LENGTH,  0x00112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF,
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_TOKEN,        sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_LABEL,        12,                      0x58464753U, 0x425550U, 0x00383231U      /* 'SGFX', 'PUB', '128' */
  }
};

/* Stop placing data in specified section*/
#if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__CC_ARM)
#pragma arm section code
#elif defined(__GNUC__)
#pragma GCC pop_options
#endif

/* USER CODE END KMS_PLATF_OBJECTS_CONFIG_Embedded_Objects_Definition */

/** @addtogroup KMS_PLATF_Private_Variables Private Variables
  * @{
  */
/**
  * @brief  KMS embedded objects definition
  * @note   Must contains KMS blob verification and decryption keys
  */
const kms_obj_keyhead_t *const KMS_PlatfObjects_EmbeddedList[KMS_INDEX_MAX_EMBEDDED_OBJECTS -
                                                             KMS_INDEX_MIN_EMBEDDED_OBJECTS + 1] =
{
/* USER CODE BEGIN KMS_PlatfObjects_EmbeddedList */
  /* UserApp example keys */
  (kms_obj_keyhead_t *) &Sigfox_Data_Key,            /* Index = 1 */
  (kms_obj_keyhead_t *) &Sigfox_pac,                 /* Index = 2 */
  (kms_obj_keyhead_t *) &Sigfox_id,                  /* Index = 3 */
  (kms_obj_keyhead_t *) &Sigfox_Public_Key,          /* Index = 4 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 5 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 6 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 7 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 8 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 9 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 10 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 11 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 12 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 13 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 14 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 15 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 16 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 17 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 18 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 19 */
  (kms_obj_keyhead_t *) NULL,       /* Index = 20 */
/* USER CODE END KMS_PlatfObjects_EmbeddedList */
};

/**
  * @}
  */
#endif /* KMS_PLATF_OBJECTS_C */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* KMS_PLATF_OBJECTS_CONFIG_H */

