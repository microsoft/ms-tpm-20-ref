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
//** Description
// This file contains the entry point for the simulator.

//** Includes, Defines, Data Definitions, and Function Prototypes
#include "TpmBuildSwitches.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include "BaseTypes.h"

#ifdef _MSC_VER
#include <windows.h>
#include <winsock.h>
#elif defined(__unix__)
#define _strcmpi strcasecmp
typedef int SOCKET;
#else
#error "Unsupported platform."
#endif

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#include "TpmTcpProtocol.h"
#include "Manufacture_fp.h"
#include "Platform_fp.h"
#include "Simulator_fp.h"

#define PURPOSE \
"TPM Reference Simulator.\nCopyright Microsoft Corp.\n"

#define DEFAULT_TPM_PORT 2321

//** Functions

//*** Usage()
// This function prints the proper calling sequence for the simulator.
static void
Usage(
    char                *pszProgramName
    )
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "%s         - Starts the TPM server listening on port %d\n",
              pszProgramName, DEFAULT_TPM_PORT);
    fprintf(stderr,
              "%s PortNum - Starts the TPM server listening on port PortNum\n",
              pszProgramName);
    fprintf(stderr, "%s ?       - This message\n", pszProgramName);
    exit(1);
}

//*** main()
// This is the main entry point for the simulator. 
// It registers the interface and starts listening for clients
int
main(
    int              argc,
    char            *argv[]
    )
{
    int portNum = DEFAULT_TPM_PORT;
    if(argc > 2)
    {
        Usage(argv[0]);
    }

    if(argc == 2)
    {
        if(strcmp(argv[1], "?") == 0)
        {
            Usage(argv[0]);
        }
        portNum = atoi(argv[1]);
        if(portNum <= 0 || portNum > 65535)
        {
            Usage(argv[0]);
        }
    }
    _plat__NVEnable(NULL);

    if(TPM_Manufacture(1) != 0)
    {
        exit(1);
    }
    // Coverage test - repeated manufacturing attempt
    if(TPM_Manufacture(0) != 1)
    {
        exit(2);
    }
    // Coverage test - re-manufacturing
    TPM_TearDown();
    if(TPM_Manufacture(1) != 0)
    {
        exit(3);
    }
    // Disable NV memory
    _plat__NVDisable();

    StartTcpServer(portNum);
    return EXIT_SUCCESS;
}

