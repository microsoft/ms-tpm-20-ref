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
/*(Auto-generated)
 *  Created by TpmPrototypes; Version 3.0 July 18, 2017
 *  Date: Mar  4, 2020  Time: 02:36:44PM
 */

#ifndef    _TABLE_DRIVEN_MARSHAL_FP_H_
#define    _TABLE_DRIVEN_MARSHAL_FP_H_

#if TABLE_DRIVEN_MARSHAL

//***UnmarshalUnion()
TPM_RC
UnmarshalUnion(
    UINT16               typeIndex,         // IN: the thing to unmarshal
    void                *target,            // IN: were the data goes to
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size,              // IN/OUT: the remaining size
    UINT32               selector
);

//*** MarshalUnion()
UINT16
MarshalUnion(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *source,            // IN: were the data comes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size,              // IN/OUT: the remaining size
    UINT32               selector           // IN: the union selector
);

TPM_RC
UnmarshalInteger(
    int                  iSize,             // IN: Number of bytes in the integer
    void                *target,            // OUT: receives the integer
    UINT8               **buffer,           // IN/OUT: source of the data
    INT32               *size,              // IN/OUT: amount of data available
    UINT32              *value              // OUT: optional copy of 'target'
);

//*** Unmarshal()
// This is the function that performs unmarshaling of different numbered types. Each
// TPM type has a number. The number is used to lookup the address of the data
// structure that describes how to unmarshal that data type.
//
TPM_RC
Unmarshal(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *target,            // IN: were the data goes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size               // IN/OUT: the remaining size
);

//*** Marshal()
// This is the function that drives marshaling of output. Because there is no
// validation of the output, there is a lot less code.
UINT16 Marshal(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *source,            // IN: were the data comes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size               // IN/OUT: the remaining size
);
#endif // TABLE_DRIVEN_MARSHAL

#endif  // _TABLE_DRIVEN_MARSHAL_FP_H_
