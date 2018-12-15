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
//
// This file contains the socket interface to a TPM simulator.
//
//** Includes, Locals, Defines and Function Prototypes
#include "TpmBuildSwitches.h"

#include <stdio.h>

#ifdef _MSC_VER
#include <windows.h>
#include <winsock.h>
typedef int socklen_t;
#elif defined(__unix__)
#  include <string.h>
#  define ZeroMemory(ptr, sz) (memset((ptr), 0, (sz)))
#  include <unistd.h>
#  define closesocket(x) close(x)
#  define INVALID_SOCKET (-1)
#  define SOCKET_ERROR   (-1)
typedef int SOCKET;
#  include <errno.h>
#  define WSAGetLastError() (errno)
#  include <stdint.h>
#  define INT_PTR intptr_t
#  include <netinet/in.h>
#  include <sys/socket.h>
#endif


#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "BaseTypes.h"

#include "TpmTcpProtocol.h"
#include "Manufacture_fp.h"

#include "Simulator_fp.h"

// To access key cache control in TPM
void RsaKeyCacheControl(int state);

#ifndef __IGNORE_STATE__

static uint32_t ServerVersion = 1;

#define MAX_BUFFER 1048576
char InputBuffer[MAX_BUFFER];       //The input data buffer for the simulator.
char OutputBuffer[MAX_BUFFER];      //The output data buffer for the simulator.

struct
{
    uint32_t    largestCommandSize;
    uint32_t    largestCommand;
    uint32_t    largestResponseSize;
    uint32_t    largestResponse;
} CommandResponseSizes = {0};

#endif // __IGNORE_STATE___

//** Functions

//*** CreateSocket()
// This function creates a socket listening on 'PortNumber'.
static int
CreateSocket(
    int                  PortNumber,
    SOCKET              *listenSocket
    )
{
    struct               sockaddr_in MyAddress;
    int res;
//  
    // Initialize Winsock
#ifdef _MSC_VER
    WSADATA              wsaData;
    res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(res != 0)
    {
        printf("WSAStartup failed with error: %d\n", res);
        return -1;
    }
#endif
    // create listening socket
    *listenSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(INVALID_SOCKET == *listenSocket)
    {
        printf("Cannot create server listen socket.  Error is 0x%x\n",
               WSAGetLastError());
        return -1;
    }
    // bind the listening socket to the specified port
    ZeroMemory(&MyAddress, sizeof(MyAddress));
    MyAddress.sin_port = htons((short)PortNumber);
    MyAddress.sin_family = AF_INET;

    res = bind(*listenSocket, (struct sockaddr*) &MyAddress, sizeof(MyAddress));
    if(res == SOCKET_ERROR)
    {
        printf("Bind error.  Error is 0x%x\n", WSAGetLastError());
        return -1;
    }
    // listen/wait for server connections
    res = listen(*listenSocket, 3);
    if(res == SOCKET_ERROR)
    {
        printf("Listen error.  Error is 0x%x\n", WSAGetLastError());
        return -1;
    }
    return 0;
}

//*** PlatformServer()
// This function processes incoming platform requests.
BOOL
PlatformServer(
    SOCKET           s
    )
{
    BOOL                 OK = TRUE;
    uint32_t             Command;
//
    for(;;)
    {
        OK = ReadBytes(s, (char*)&Command, 4);
        // client disconnected (or other error).  We stop processing this client
        // and return to our caller who can stop the server or listen for another
        // connection.
        if(!OK) return TRUE;
        Command = ntohl(Command);
        switch(Command)
        {
            case TPM_SIGNAL_POWER_ON:
                _rpc__Signal_PowerOn(FALSE);
                break;
            case TPM_SIGNAL_POWER_OFF:
                _rpc__Signal_PowerOff();
                break;
            case TPM_SIGNAL_RESET:
                _rpc__Signal_PowerOn(TRUE);
                break;
            case TPM_SIGNAL_RESTART:
                _rpc__Signal_Restart();
                break;
            case TPM_SIGNAL_PHYS_PRES_ON:
                _rpc__Signal_PhysicalPresenceOn();
                break;
            case TPM_SIGNAL_PHYS_PRES_OFF:
                _rpc__Signal_PhysicalPresenceOff();
                break;
            case TPM_SIGNAL_CANCEL_ON:
                _rpc__Signal_CancelOn();
                break;
            case TPM_SIGNAL_CANCEL_OFF:
                _rpc__Signal_CancelOff();
                break;
            case TPM_SIGNAL_NV_ON:
                _rpc__Signal_NvOn();
                break;
            case TPM_SIGNAL_NV_OFF:
                _rpc__Signal_NvOff();
                break;
            case TPM_SIGNAL_KEY_CACHE_ON:
                _rpc__RsaKeyCacheControl(TRUE);
                break;
            case TPM_SIGNAL_KEY_CACHE_OFF:
                _rpc__RsaKeyCacheControl(FALSE);
                break;
            case TPM_SESSION_END:
                // Client signaled end-of-session
                TpmEndSimulation();
                return TRUE;
            case TPM_STOP:
                // Client requested the simulator to exit
                return FALSE;
            case TPM_TEST_FAILURE_MODE:
                _rpc__ForceFailureMode();
                break;
            case TPM_GET_COMMAND_RESPONSE_SIZES:
                OK = WriteVarBytes(s, (char *)&CommandResponseSizes,
                                   sizeof(CommandResponseSizes));
                memset(&CommandResponseSizes, 0, sizeof(CommandResponseSizes));
                if(!OK)
                    return TRUE;
                break;
            default:
                printf("Unrecognized platform interface command %d\n", 
                       (int)Command);
                WriteUINT32(s, 1);
                return TRUE;
        }
        WriteUINT32(s, 0);
    }
    return FALSE;
}

//*** PlatformSvcRoutine()
// This function is called to set up the socket interfaces to listen for
// commands.
DWORD WINAPI
PlatformSvcRoutine(
    LPVOID           port
    )
{
    int                  PortNumber = (int)(INT_PTR)port;
    SOCKET               listenSocket, serverSocket;
    struct               sockaddr_in HerAddress;
    int                  res;
    socklen_t            length;
    BOOL                 continueServing;
//
    res = CreateSocket(PortNumber, &listenSocket);
    if(res != 0)
    {
        printf("Create platform service socket fail\n");
        return res;
    }
    // Loop accepting connections one-by-one until we are killed or asked to stop
    // Note the platform service is single-threaded so we don't listen for a new
    // connection until the prior connection drops.
    do
    {
        printf("Platform server listening on port %d\n", PortNumber);

        // blocking accept
        length = sizeof(HerAddress);
        serverSocket = accept(listenSocket,
                              (struct sockaddr*) &HerAddress,
                              &length);
        if(serverSocket == SOCKET_ERROR)
        {
            printf("Accept error.  Error is 0x%x\n", WSAGetLastError());
            return -1;
        }
        printf("Client accepted\n");

        // normal behavior on client disconnection is to wait for a new client
        // to connect
        continueServing = PlatformServer(serverSocket);
        closesocket(serverSocket);
    } while(continueServing);

    return 0;
}

//*** PlatformSignalService()
// This function starts a new thread waiting for platform signals.
// Platform signals are processed one at a time in the order in which they are
// received.
#if defined(_MSC_VER)
int
PlatformSignalService(
    int              PortNumber
    )
{
    HANDLE               hPlatformSvc;
    int                  ThreadId;
    int                  port = PortNumber;
//
    // Create service thread for platform signals
    hPlatformSvc = CreateThread(NULL, 0,
                                (LPTHREAD_START_ROUTINE)PlatformSvcRoutine,
                                (LPVOID)(INT_PTR)port, 0, (LPDWORD)&ThreadId);
    if(hPlatformSvc == NULL)
    {
        printf("Thread Creation failed\n");
        return -1;
    }
    return 0;
}
#elif defined(__unix__)
#include <pthread.h>
int
PlatformSignalService(
    int              PortNumber
    )
{
    pthread_t thread_id;
    int ret;
    int port = PortNumber;

    ret = pthread_create(&thread_id, NULL, (void*)PlatformSvcRoutine, (LPVOID)(INT_PTR)port);
    if (ret == -1)
    {
        printf("pthread_create failed: %s", strerror(ret));
    }

    return ret;
}
#else
#error "Unsupported platform."
#endif // _MSC_VER
//*** RegularCommandService()
// This function services regular commands.
int
RegularCommandService(
    int              PortNumber
    )
{
    SOCKET               listenSocket;
    SOCKET               serverSocket;
    struct               sockaddr_in HerAddress;
    int                  res;
    socklen_t            length;
    BOOL                 continueServing;
//
    res = CreateSocket(PortNumber, &listenSocket);
    if(res != 0)
    {
        printf("Create platform service socket fail\n");
        return res;
    }
    // Loop accepting connections one-by-one until we are killed or asked to stop
    // Note the TPM command service is single-threaded so we don't listen for
    // a new connection until the prior connection drops.
    do
    {
        printf("TPM command server listening on port %d\n", PortNumber);

        // blocking accept
        length = sizeof(HerAddress);
        serverSocket = accept(listenSocket,
                              (struct sockaddr*) &HerAddress,
                              &length);
        if(serverSocket == SOCKET_ERROR)
        {
            printf("Accept error.  Error is 0x%x\n", WSAGetLastError());
            return -1;
        }
        printf("Client accepted\n");

        // normal behavior on client disconnection is to wait for a new client
        // to connect
        continueServing = TpmServer(serverSocket);
        closesocket(serverSocket);
    } while(continueServing);
    return 0;
}

//*** StartTcpServer()
// This is the main entry-point to the TCP server.  The server listens on port 
// specified.
//
// Note that there is no way to specify the network interface in this implementation.
int
StartTcpServer(
    int              PortNumber
    )
{
    int                  res;
//
    // Start Platform Signal Processing Service
    res = PlatformSignalService(PortNumber + 1);
    if(res != 0)
    {
        printf("PlatformSignalService failed\n");
        return res;
    }
    // Start Regular/DRTM TPM command service
    res = RegularCommandService(PortNumber);
    if(res != 0)
    {
        printf("RegularCommandService failed\n");
        return res;
    }
    return 0;
}

//*** ReadBytes()
// This function reads the indicated number of bytes ('NumBytes') into buffer
// from the indicated socket.
BOOL
ReadBytes(
    SOCKET           s,
    char            *buffer,
    int              NumBytes
    )
{
    int                  res;
    int                  numGot = 0;
//
    while(numGot < NumBytes)
    {
        res = recv(s, buffer + numGot, NumBytes - numGot, 0);
        if(res == -1)
        {
            printf("Receive error.  Error is 0x%x\n", WSAGetLastError());
            return FALSE;
        }
        if(res == 0)
        {
            return FALSE;
        }
        numGot += res;
    }
    return TRUE;
}

//*** WriteBytes()
// This function will send the indicated number of bytes ('NumBytes') to the
// indicated socket
BOOL
WriteBytes(
    SOCKET           s,
    char            *buffer,
    int              NumBytes
    )
{
    int                  res;
    int                  numSent = 0;
//
    while(numSent < NumBytes)
    {
        res = send(s, buffer + numSent, NumBytes - numSent, 0);
        if(res == -1)
        {
            if(WSAGetLastError() == 0x2745)
            {
                printf("Client disconnected\n");
            }
            else
            {
                printf("Send error.  Error is 0x%x\n", WSAGetLastError());
            }
            return FALSE;
        }
        numSent += res;
    }
    return TRUE;
}

//*** WriteUINT32()
// Send 4 bytes containing hton(1)
BOOL
WriteUINT32(
    SOCKET           s,
    uint32_t         val
    )
{
    UINT32 netVal = htonl(val);
//
    return WriteBytes(s, (char*)&netVal, 4);
}

//*** ReadVarBytes()
// Get a UINT32-length-prepended binary array.  Note that the 4-byte length is
// in network byte order (big-endian).
BOOL
ReadVarBytes(
    SOCKET           s,
    char            *buffer,
    uint32_t        *BytesReceived,
    int              MaxLen
    )
{
    int                  length;
    BOOL                 res;
//
    res = ReadBytes(s, (char*)&length, 4);
    if(!res) return res;
    length = ntohl(length);
    *BytesReceived = length;
    if(length > MaxLen)
    {
        printf("Buffer too big.  Client says %d\n", length);
        return FALSE;
    }
    if(length == 0) return TRUE;
    res = ReadBytes(s, buffer, length);
    if(!res) return res;
    return TRUE;
}

//*** WriteVarBytes()
// Send a UINT32-length-prepended binary array.  Note that the 4-byte length is
// in network byte order (big-endian).
BOOL
WriteVarBytes(
    SOCKET           s,
    char            *buffer,
    int              BytesToSend
    )
{
    uint32_t             netLength = htonl(BytesToSend);
    BOOL res;
//
    res = WriteBytes(s, (char*)&netLength, 4);
    if(!res) 
        return res;
    res = WriteBytes(s, buffer, BytesToSend);
    if(!res) 
        return res;
    return TRUE;
}

//*** TpmServer()
// Processing incoming TPM command requests using the protocol / interface
// defined above.
BOOL
TpmServer(
    SOCKET           s
    )
{
    uint32_t             length;
    uint32_t             Command;
    BYTE                 locality;
    BOOL                 OK;
    int                  result;
    int                  clientVersion;
    _IN_BUFFER           InBuffer;
    _OUT_BUFFER          OutBuffer;
//
    for(;;)
    {
        OK = ReadBytes(s, (char*)&Command, 4);
        // client disconnected (or other error).  We stop processing this client
        // and return to our caller who can stop the server or listen for another
        // connection.
        if(!OK)
            return TRUE;
        Command = ntohl(Command);
        switch(Command)
        {
            case TPM_SIGNAL_HASH_START:
                _rpc__Signal_Hash_Start();
                break;
            case TPM_SIGNAL_HASH_END:
                _rpc__Signal_HashEnd();
                break;
            case TPM_SIGNAL_HASH_DATA:
                OK = ReadVarBytes(s, InputBuffer, &length, MAX_BUFFER);
                if(!OK) return TRUE;
                InBuffer.Buffer = (BYTE*)InputBuffer;
                InBuffer.BufferSize = length;
                _rpc__Signal_Hash_Data(InBuffer);
                break;
            case TPM_SEND_COMMAND:
                OK = ReadBytes(s, (char*)&locality, 1);
                if(!OK)
                    return TRUE;
                OK = ReadVarBytes(s, InputBuffer, &length, MAX_BUFFER);
                if(!OK)
                    return TRUE;
                InBuffer.Buffer = (BYTE*)InputBuffer;
                InBuffer.BufferSize = length;
                OutBuffer.BufferSize = MAX_BUFFER;
                OutBuffer.Buffer = (_OUTPUT_BUFFER)OutputBuffer;
                // record the number of bytes in the command if it is the largest
                // we have seen so far.
                if(InBuffer.BufferSize > CommandResponseSizes.largestCommandSize)
                {
                    CommandResponseSizes.largestCommandSize = InBuffer.BufferSize;
                    memcpy(&CommandResponseSizes.largestCommand,
                           &InputBuffer[6], sizeof(UINT32));
                }
                _rpc__Send_Command(locality, InBuffer, &OutBuffer);
                // record the number of bytes in the response if it is the largest
                // we have seen so far.
                if(OutBuffer.BufferSize > CommandResponseSizes.largestResponseSize)
                {
                    CommandResponseSizes.largestResponseSize
                        = OutBuffer.BufferSize;
                    memcpy(&CommandResponseSizes.largestResponse,
                           &OutputBuffer[6], sizeof(UINT32));
                }
                OK = WriteVarBytes(s,
                                   (char*)OutBuffer.Buffer,
                                   OutBuffer.BufferSize);
                if(!OK)
                    return TRUE;
                break;
            case TPM_REMOTE_HANDSHAKE:
                OK = ReadBytes(s, (char*)&clientVersion, 4);
                if(!OK)
                    return TRUE;
                if(clientVersion == 0)
                {
                    printf("Unsupported client version (0).\n");
                    return TRUE;
                }
                OK &= WriteUINT32(s, ServerVersion);
                OK &= WriteUINT32(s, tpmInRawMode 
                                  | tpmPlatformAvailable | tpmSupportsPP);
                break;
            case TPM_SET_ALTERNATIVE_RESULT:
                OK = ReadBytes(s, (char*)&result, 4);
                if(!OK)
                    return TRUE;
                // Alternative result is not applicable to the simulator.
                break;
            case TPM_SESSION_END:
                // Client signaled end-of-session
                return TRUE;
            case TPM_STOP:
                // Client requested the simulator to exit
                return FALSE;
            default:
                printf("Unrecognized TPM interface command %d\n", (int)Command);
                return TRUE;
        }
        OK = WriteUINT32(s, 0);
        if(!OK)
            return TRUE;
    }
    return FALSE;
}