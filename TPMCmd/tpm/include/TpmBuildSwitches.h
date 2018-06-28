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
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
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
// This file contains the build switches. This contains switches for multiple
// versions of the crypto-library so some may not apply to your environment.
//
// The switches are guarded so that they can either be set on the command line or
// set here.

#ifndef _TPM_BUILD_SWITCHES_H_
#define _TPM_BUILD_SWITCHES_H_


#undef YES
#define YES 1
#undef NO
#define NO 0

// Need an unambiguous definition for DEBUG. Don't change this
#if !defined NDEBUG
#   if !defined DEBUG || DEBUG != NO
#       undef DEBUG
#       define DEBUG YES
#   endif
#endif
#if !defined DEBUG
#   define DEBUG NO
#endif

#include "CompilerDependencies.h"

// This definition is required for the re-factored code
#if !defined USE_BN_ECC_DATA || USE_BN_ECC_DATA != NO
#   undef  USE_BN_ECC_DATA
#   define USE_BN_ECC_DATA YES
#endif

// Modify these as needed
#if !defined SIMULATION || SIMULATION != NO
#   undef SIMULATION
#   define SIMULATION   YES
#endif

// Define this to run the function that checks the format compatibility for the
// chosen big number math library. Not all ports use this.
#if !defined LIBRARY_COMPATIBILITY_CHECK                                           \
        || LIBRARY_COMPATIBILITY_CHECK != YES
#   undef LIBRARY_COMPATIBILITY_CHECK
#   define LIBRARY_COMPATIBILITY_CHECK NO
#endif


#if !defined FIPS_COMPLIANT || FIPS_COMPLIANT != NO
#   undef FIPS_COMPLIANT
#  define FIPS_COMPLIANT YES
#endif

// Definition to allow alternate behavior for non-orderly startup. If there is a
// chance that the TPM could not update 'failedTries'
#if !defined USE_DA_USED || USE_DA_USED != NO
#   undef USE_DA_USED
#   define USE_DA_USED YES
#endif

// Define TABLE_DRIVEN_DISPATCH to use tables rather than case statements
// for command dispatch and handle unmarshaling
#if !defined TABLE_DRIVEN_DISPATCH || TABLE_DRIVEN_DISPATCH != NO
#   undef TABLE_DRIVEN_DISPATCH
#   define TABLE_DRIVEN_DISPATCH YES
#endif

// This switch is used to enable the self-test capability in AlgorithmTests.c
#if !defined SELF_TEST || SELF_TEST != NO
#   undef SELF_TEST
#   define SELF_TEST YES
#endif

// Enable the generation of RSA primes using a sieve.
#if !defined RSA_KEY_SIEVE || RSA_KEY_SIEVE != NO
#   undef RSA_KEY_SIEVE
#   define RSA_KEY_SIEVE YES
#endif

// Enable the instrumentation of the sieve process. This is used to tune the sieve
// variables. 
#if RSA_KEY_SIEVE && SIMULATION
#   if !defined RSA_INSTRUMENT || RSA_INSTRUMENT != YES
#       undef RSA_INSTRUMENT
#       define RSA_INSTRUMENT NO    // change this to enable instrumentation
#   endif
#else
#   undef RSA_INSTRUMENT
#   define RSA_INSTRUMENT NO
#endif

// This switch enables the RNG state save and restore
#if !defined _DRBG_STATE_SAVE || _DRBG_STATE_SAVE != NO
#   undef _DRBG_STATE_SAVE
#   define _DRBG_STATE_SAVE YES
#endif

// Switch added to support packed lists that leave out space associated with
// unimplemented commands. Comment this out to use linear lists.
// Note: if vendor specific commands are present, the associated list is always
// in compressed form.
#if !defined COMPRESSED_LISTS || COMPRESSED_LISTS != NO
#   undef COMPRESSED_LISTS
#   define COMPRESSED_LISTS YES
#endif

// This switch indicates where clock epoch value should be stored. If this value
// defined, then it is assumed that the timer will change at any time so the
// nonce should be a random number kept in RAM. When it is not defined, then the
// timer only stops during power outages.
#if !defined CLOCK_STOPS || CLOCK_STOPS != YES
#   undef CLOCK_STOPS
#   define CLOCK_STOPS NO
#endif

// This switch allows use of #defines in place of pass-through marshaling or 
// unmarshaling code. A pass-through function just calls another function to do 
// the required function and does no parameter checking of its own. The
// table-driven dispatcher calls directly to the lowest level
// marshaling/unmarshaling code and by-passes any pass-through functions so, for
// that code. If #defines are used in other code, then no code is generated for
// a pass-through marshaling/unmarshaling function.
#if !defined USE_MARSHALING_DEFINES || USE_MARSHALING_DEFINES != NO
#   undef USE_MARSHALING_DEFINES
#   define USE_MARSHALING_DEFINES YES
#endif

//**********************************
// The switches in this group can only be enabled when running a simulation
#if SIMULATION
// Enables use of the key cache
#   if !defined USE_RSA_KEY_CACHE || USE_RSA_KEY_CACHE != NO
#       undef USE_RSA_KEY_CACHE
#       define USE_RSA_KEY_CACHE YES
#   endif
#   if !defined USE_KEY_CACHE_FILE || USE_KEY_CACHE_FILE != NO
#       undef USE_KEY_CACHE_FILE
#       define USE_KEY_CACHE_FILE YES
#   endif
#   if DEBUG && !defined USE_DEBUG_RNG
// This provides fixed seeding of the RNG when doing debug on a simulator. This
// should allow consistent results on test runs as long as the input parameters
// to the functions remains the same.
#       undef USE_DEBUG_RNG
#       define USE_DEBUG_RNG YES // Either YES or NO
#   endif
#else
// Don't change these. They are the settings needed when not doing a simulation
# define USE_RSA_KEY_CACHE NO
# define USE_KEY_CACHE_FILE NO
# define USE_DEBUG_RNG NO
#endif  // SIMULATION

#if DEBUG

// In some cases, the relationship between two values may be dependent
// on things that change based on various selections like the chosen cryptographic
// libraries. It is possible that these selections will result in incompatible
// settings. These are often detectable by the compiler but it isn't always 
// possible to do the check in the preprocessor code. For example, when the
// check requires use of 'sizeof()' then the preprocessor can't do the comparison.
// For these cases, we include a special macro that, depending on the compiler
// will generate a warning to indicate if the check always passes or always fails
// because it involves fixed constants. To run these checks, define COMPILER_CHECKS.
#if !defined COMPILER_CHECKS || COMPILER_CHECKS != YES
#   undef COMPILER_CHECKS
#   define COMPILER_CHECKS NO
#endif

// Some of the values (such as sizes) are the result of different options set in 
// Implementation.h. The combination might not be consistent. A function is defined
// (TpmSizeChecks()) that is used to verify the sizes at run time. To enable the 
// function, define this parameter.
#if !defined RUNTIME_SIZE_CHECKS || RUNTIME_SIZE_CHECKS != NO
#   undef RUNTIME_SIZE_CHECKS
#   define RUNTIME_SIZE_CHECKS YES
#endif

// If doing debug, can set the DRBG to print out the intermediate test values. 
// Before enabling this, make sure that the dbgDumpMemBlock() function
// has been added someplace (preferably, somewhere in CryptRand.c)
#if !defined DRBG_DEBUG_PRINT || DRBG_DEBUG_PRINT != YES
#   undef DRBG_DEBUG_PRINT
#   define DRBG_DEBUG_PRINT NO
#endif

// If an assertion event it not going to produce any trace information (function and
// line number) then make FAIL_TRACE == NO
#if !defined FAIL_TRACE || FAIL_TRACE != NO
#   undef FAIL_TRACE
#   define FAIL_TRACE YES
#endif

#endif // DEBUG

// If the implementation is going to give lockout time credit for time up to the
// last orderly shutdown, then uncomment this variable
#if !defined ACCUMULATE_SELF_HEAL_TIMER || ACCUMULATE_SELF_HEAL_TIMER != NO
#   undef ACCUMULATE_SELF_HEAL_TIMER
#   define ACCUMULATE_SELF_HEAL_TIMER YES
#endif // ACCUMULATE_SELF_HEAL_TIMER

// If the implementation is to compute the sizes of the proof and primary seed size
// values based on the implemented algorithms, then use this define.
#if !defined USE_SPEC_COMPLIANT_PROOFS || USE_SPEC_COMPLIANT_PROOFS != NO
#   undef USE_SPEC_COMPLIANT_PROOFS
#   define  USE_SPEC_COMPLIANT_PROOFS YES
#endif

// Comment this out to allow compile to continue even though the chosen proof values
// do not match the compliant values. This is written so that someone would
// have to proactively ignore errors.
#if !defined SKIP_PROOF_ERRORS || SKIP_PROOF_ERRORS != YES 
#   undef SKIP_PROOF_ERRORS
#   define SKIP_PROOF_ERRORS NO
#endif

// This define is used to eliminate the use of bit-fields. It can be enable for
// big- or little-endian machines but is required of big-endian system that number
// bits in registers from left to right. Little-endian machines number from right 
// to left with the least significant bit having assigned a bit number of 0. These
// are LSb0 machines (they are also little-endian so they are also least-significant
// byte 0 (LSB0) machines. Big-endian (MSB0) machines may number in either direction
// (MSb0 or LSb0). For an MSB0+MSb0 machine this value should be 'NO'
#if !defined USE_BIT_FIELD_STRUCTURES || USE_BIT_FIELD_STRUCTURES != NO
#   undef USE_BIT_FIELD_STRUCTURES
#   define USE_BIT_FIELD_STRUCTURES YES
#endif

// Change these definitions to turn all algorithms or commands ON or OFF. That is,
// to turn all algorithms on, set ALG_NO to YES. This is mostly useful as a debug
// feature.
#define      ALG_YES      YES
#define      ALG_NO       NO
#define      CC_YES       YES
#define      CC_NO        NO

#endif // _TPM_BUILD_SWITCHES_H_