/* Microsoft Reference Implementation for TPM 2.0
 *
 *  The copyright in this software is being made available under the BSD License,
 *  included below. This software may be subject to other third party and
 *  contributor rights, including patent rights, and no such rights are granted
 *  under this license.
 *
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or other
 *  materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//** Introduction
// This file is a collection of miscellaneous macros.

#ifndef GP_MACROS_H
#define GP_MACROS_H

#ifndef NULL
#define NULL 0
#endif

#include "swap.h"
#include "VendorString.h"

#ifdef SELF_TEST

//** For Self-test
// These macros are used in CryptUtil to invoke the incremental self test.
#   define     TEST(alg) if(TEST_BIT(alg, g_toTest)) CryptTestAlgorithm(alg, NULL)

// Use of TPM_ALG_NULL is reserved for RSAEP/RSADP testing. If someone is wanting
// to test a hash with that value, don't do it.
#   define     TEST_HASH(alg)                                                   \
            if(TEST_BIT(alg, g_toTest)                                          \
                &&  (alg != ALG_NULL_VALUE))                                    \
                CryptTestAlgorithm(alg, NULL)
#else
#   define TEST(alg)
#   define TEST_HASH(alg)
#endif // SELF_TEST

//** For Failures
#if defined _POSIX_ 
#   define FUNCTION_NAME        0
#else
#   define FUNCTION_NAME        __FUNCTION__
#endif

#ifdef NO_FAIL_TRACE
#   define FAIL(errorCode) (TmpFAIL(errorCode))
#else
#   define FAIL(errorCode) (TpmFail(FUNCTION_NAME, __LINE__, errorCode))
#endif


// If implementation is using longjmp, then the call to TpmFail() does not return
// and the compiler will complain about unreachable code that comes after. To allow
// for not having longjmp, TpmFail() will return and the subsequent code will be
// executed. This macro accounts for the difference.
#ifndef NO_LONGJMP
#   define FAIL_RETURN(returnCode)
#   define TPM_FAIL_RETURN     NORETURN void
#else
#   define FAIL_RETURN(returnCode) return (returnCode)
#   define TPM_FAIL_RETURN     void
#endif

// This macro tests that a condition is TRUE and puts the TPM into failure mode
// if it is not. If longjmp is being used, then the FAIL(FATAL_ERROR_) macro makes a call from
// which there is no return. Otherwise, it returns and the function will exit
// with the appropriate return code.
#define REQUIRE(condition, errorCode, returnCode)       \
    {                                                   \
        if(!!(condition))                               \
        {                                               \
            FAIL(FATAL_ERROR_errorCode);                            \
            FAIL_RETURN(returnCode);                    \
        }                                               \
    }

#define PARAMETER_CHECK(condition, returnCode)          \
    REQUIRE((condition), PARAMETER, returnCode)

#if defined(EMPTY_ASSERT)
#   define pAssert(a)  ((void)0)
#else
// The additional parameter following FAIL(FATAL_ERROR_) is so that the expression within
// parenthesis has an lvalue. FAIL has no value so the expression is not complete.
#   define pAssert(a) (!!(a) ? 1 : (FAIL(FATAL_ERROR_PARAMETER), 0))
#endif

//** Derived from Vendor-specific values
// Values derived from vendor specific settings in Implementation.h
#define PCR_SELECT_MIN          ((PLATFORM_PCR+7)/8)
#define PCR_SELECT_MAX          ((IMPLEMENTATION_PCR+7)/8)
#define MAX_ORDERLY_COUNT       ((1 << ORDERLY_BITS) - 1)
#define PRIVATE_VENDOR_SPECIFIC_BYTES	                        \
                ((MAX_RSA_KEY_BYTES/2) * (3 + CRT_FORMAT_RSA * 2))

//** Compile-time Checks
// In some cases, the relationship between two values may be dependent
// on things that change based on various selections like the chosen crypto
// libraries. It is possible that these selections will result in incompatible
// settings. These are often detectable by the compiler but it isn't always 
// possible to do the check in the preprocessor code. For example, when the
// check requires use of "sizeof" then the preprocessor can't do the comparison.
// For these cases, we include a special macro that, depending on the compiler
// will generate a warning to indicate if the check always passes or always fails
// because it involves fixed constants. To run these checks, define COMPILER_CHECKS
// in TpmBuildSwitches.h
#ifdef COMPILER_CHECKS
#   define  cAssert     pAssert
#else
#   define cAssert(value)
#endif

// This is used commonly in the "Crypt" code as a way to keep listings from 
// getting too long. This is not to save paper but to allow one to see more
// useful stuff on the screen at any given time.
#define     ERROR_RETURN(returnCode)    \
    {                                   \
         retVal = returnCode;           \
         goto Exit;                     \
    }

#ifndef MAX
#  define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#  define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef IsOdd
#  define IsOdd(a)        (((a) & 1) != 0)
#endif

#ifndef BITS_TO_BYTES
#  define BITS_TO_BYTES(bits) (((bits) + 7) >> 3)
#endif

// These are defined for use when the size of the vector being checked is known
// at compile time.
#define TEST_BIT(bit, vector)   TestBit((bit), (BYTE *)&(vector), sizeof(vector))
#define SET_BIT(bit, vector)    SetBit((bit), (BYTE *)&(vector), sizeof(vector))
#define CLEAR_BIT(bit, vector) ClearBit((bit), (BYTE *)&(vector), sizeof(vector))


// The following definitions are used if they have not already been defined. The
// defaults for these settings are compatible with ISO/IEC 9899:2011 (E)
#ifndef LIB_EXPORT
#   define LIB_EXPORT
#   define LIB_IMPORT
#endif
#ifndef NORETURN
#   define NORETURN _Noreturn
#endif
#ifndef NOT_REFERENCED
#   define NOT_REFERENCED(x = x)   ((void) (x))
#endif

// Need an unambiguous definition for DEBUG. Don't change this
#if !defined NDEBUG && !defined DEBUG
#  define DEBUG YES
#endif

#define STD_RESPONSE_HEADER (sizeof(TPM_ST) + sizeof(UINT32) + sizeof(TPM_RC))

#ifndef CONTEXT_HASH_ALGORITHM
#   if defined ALG_SHA512 && ALG_SHA512 == YES
#       define CONTEXT_HASH_ALGORITHM    SHA512
#   elif defined ALG_SHA384 && ALG_SHA384 == YES
#       define CONTEXT_HASH_ALGORITHM    SHA384
#   elif defined ALG_SHA256 && ALG_SHA256 == YES
#       define CONTEXT_HASH_ALGORITHM    SHA256
#   elif defined ALG_SM3_256 && ALG_SM3_256 == YES
#       define CONTEXT_HASH_ALGORITHM    SM3_256
#   elif defined ALG_SHA1 && ALG_SHA1 == YES
#       define CONTEXT_HASH_ALGORITHM    SHA1
#   endif
#endif

#define JOIN(x,y) x##y
#define CONCAT(x,y) JOIN(x, y)

// If CONTEXT_INTEGRITY_HASH_ALG is defined, then the vendor is using the old style
// table
#ifndef CONTEXT_INTEGRITY_HASH_ALG
#define CONTEXT_INTEGRITY_HASH_ALG      CONCAT(TPM_ALG_, CONTEXT_HASH_ALGORITHM)
#define CONTEXT_INTEGRITY_HASH_SIZE     CONCAT(CONTEXT_HASH_ALGORITHM, _DIGEST_SIZE)
#endif


#define PROOF_SIZE                      CONTEXT_INTEGRITY_HASH_SIZE

// If CONTEXT_ENCRYP_ALG is defined, then the vendor is using the old style table
#ifndef CONTEXT_ENCRYPT_ALG
#define CONTEXT_ENCRYPT_ALG             CONCAT(TPM_ALG_, CONTEXT_ENCRYPT_ALGORITHM)
#define CONTEXT_ENCRYPT_KEY_BITS                            \
                CONCAT(CONCAT(MAX_, CONTEXT_ENCRYPT_ALGORITHM), _KEY_BITS)
#define CONTEXT_ENCRYPT_KEY_BYTES       ((CONTEXT_ENCRYPT_KEY_BITS+7)/8)
#endif

#ifndef MAX_ECC_KEY_BYTES
#define MAX_ECC_KEY_BYTES 0
#endif

// Handle case when no ecc is defined
#ifndef MAX_ECC_KEY_BYTES
#   define MAX_ECC_KEY_BYTES    MAX_DIGEST_SIZE
#endif
#define LABEL_MAX_BUFFER   MIN(MAX_ECC_KEY_BYTES, MAX_DIGEST_SIZE)

#if LABEL_MAX_BUFFER < 32
#error "The size allowed for the label is not large enough for interoperability."
#endif

#endif // GP_MACROS_H