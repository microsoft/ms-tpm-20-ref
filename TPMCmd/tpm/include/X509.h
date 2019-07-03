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
// This file contains the macro and structure definitions for the X509 commands and
// functions.

#ifndef _X509_H_
#define _X509_H_

//** Includes

#include "Tpm.h"
#include "TpmASN1.h"

//** Defined Constants

//*** X509 Application-specific types 
#define X509_SELECTION          0xA0
#define X509_ISSUER_UNIQUE_ID   0xA1
#define X509_SUBJECT_UNIQUE_ID  0xA2
#define X509_EXTENSIONS         0xA3

// These defines give the order in which values appear in the TBScertificate
// of an x.509 certificate. These values are used to index into an array of
//
#define ENCODED_SIZE_REF        0
#define VERSION_REF             (ENCODED_SIZE_REF + 1)
#define SERIAL_NUMBER_REF       (VERSION_REF + 1)
#define SIGNATURE_REF           (SERIAL_NUMBER_REF + 1)
#define ISSUER_REF              (SIGNATURE_REF + 1)
#define VALIDITY_REF            (ISSUER_REF + 1)
#define SUBJECT_KEY_REF         (VALIDITY_REF + 1)
#define SUBJECT_PUBLIC_KEY_REF  (SUBJECT_KEY_REF + 1)
#define EXTENSIONS_REF          (SUBJECT_PUBLIC_KEY_REF + 1)
#define REF_COUNT               (EXTENSIONS_REF + 1)


//** Structures


// Used to access the fields of a TBSsignature some of which are in the in_CertifyX509
// structure and some of which are in the out_CertifyX509 structure.
typedef struct stringRef
{
    BYTE        *buf;
    INT16        len;
} stringRef;


typedef union x509KeyUsageUnion {
    TPMA_X509_KEY_USAGE     x509;
    UINT32                  integer;
} x509KeyUsageUnion;

#endif // _X509_H_
