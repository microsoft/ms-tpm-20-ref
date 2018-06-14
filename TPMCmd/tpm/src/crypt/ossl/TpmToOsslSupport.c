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
//** Introduction
//
// The functions in this file are used for initialization of the interface to the
// OpenSSL library.

//** Defines and Includes

#include "Tpm.h"

#if MATH_LIB == OSSL

// Used to pass the pointers to the correct sub-keys
typedef const BYTE *desKeyPointers[3];

//*** SupportLibInit()
// This does any initialization required by the support library.
LIB_EXPORT int
SupportLibInit(
    void
    )
{
#if LIBRARY_COMPATIBILITY_CHECK
    MathLibraryCompatibilityCheck();
#endif
    return TRUE;
}

//*** OsslContextEnter()
// This function is used to initialize an OpenSSL context at the start of a function
// that will call to an OpenSSL math function.
BN_CTX *
OsslContextEnter(
    void
    )
{
    BN_CTX              *context = BN_CTX_new();
    if(context == NULL)
        FAIL(FATAL_ERROR_ALLOCATION);
    BN_CTX_start(context);
    return context;
}

//*** OsslContextLeave()
// This is the companion function to OsslContextEnter().
void
OsslContextLeave(
    BN_CTX          *context
    )
{
    if(context != NULL)
    {
        BN_CTX_end(context);
        BN_CTX_free(context);
    }
}
#endif // MATH_LIB == OSSL

