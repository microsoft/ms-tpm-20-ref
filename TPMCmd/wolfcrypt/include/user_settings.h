/* settings.h
 *
 * Copyright (C) 2006-2017 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */


/* Place OS specific preprocessor flags, defines, includes here, will be
   included into every file because types.h includes it */


#ifndef WOLF_CRYPT_USER_SETTINGS_H
#define WOLF_CRYPT_USER_SETTINGS_H

#include <Implementation.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* Remove the automatic setting of the default I/O functions EmbedSend()
    and EmbedReceive(). */
#define WOLFSSL_USER_IO

/* Avoid naming conflicts */
#define NO_OLD_WC_NAMES

/* Use stack based fast math for all big integer math */
#define USE_FAST_MATH
#define TFM_TIMING_RESISTANT

/* Expose direct encryption functions */
#define WOLFSSL_AES_DIRECT

/* Enable/Disable algorithm support based on TPM implementation header */
#ifdef TPM_ALG_SHA256
    #define WOLFSSL_SHA256
#endif
#if defined(TPM_ALG_SHA384) || defined(TPM_ALG_SHA512)
    #define WOLFSSL_SHA384
    #define WOLFSSL_SHA512
#endif
#ifdef TPM_ALG_TDES
    #define WOLFSSL_DES_ECB
#endif
#ifdef TPM_ALG_RSA
    /* Turn on RSA key generation functionality */
    #define WOLFSSL_KEY_GEN
#endif
#ifdef TPM_ALG_ECC
    #define HAVE_ECC

    /* Expose additional ECC primitives */
    #define WOLFSSL_PUBLIC_ECC_ADD_DBL 
    #define ECC_TIMING_RESISTANT

    /* Enables Shamir calc method */
    #define ECC_SHAMIR

    /* The TPM only needs low level ECC crypto */
    #define NO_ECC_SIGN
    #define NO_ECC_VERIFY
    #define NO_ECC_SECP
#endif

/* Disable explicit RSA. The TPM support for RSA is dependent only on TFM */
#define NO_RSA
#define NO_RC4
#define NO_ASN

/* Enable debug wolf library check */
//#define LIBRARY_COMPATIBILITY_CHECK

#define WOLFSSL_

#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif
