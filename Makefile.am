## The copyright in this software is being made available under the BSD License,
## included below. This software may be subject to other third party and
## contributor rights, including patent rights, and no such rights are granted
## under this license.
##
## Copyright (c) Intel Corporation
##
## All rights reserved.
##
## BSD License
##
## Redistribution and use in source and binary forms, with or without modification,
## are permitted provided that the following conditions are met:
##
## Redistributions of source code must retain the above copyright notice, this list
## of conditions and the following disclaimer.
##
## Redistributions in binary form must reproduce the above copyright notice, this
## list of conditions and the following disclaimer in the documentation and/or
## other materials provided with the distribution.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
## DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
## ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
## (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
## ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

include src.mk

PLATFORM_INC = -I $(srcdir)/TPMCmd/Platform/include \
    -I $(srcdir)/TPMCmd/Platform/include/prototypes
SIMULATOR_INC =  -I $(srcdir)/TPMCmd/Simulator/include \
    -I $(srcdir)/TPMCmd/Simulator/include/prototypes
TPM_INC = -I $(srcdir)/TPMCmd/tpm/include \
    -I $(srcdir)/TPMCmd/tpm/include/prototypes

libplatform = TPMCmd/Platform/src/libplatform.a
libtpm = TPMCmd/tpm/src/libtpm.a
tpm2_simulator = TPMCmd/Simulator/src/tpm2-simulator

bin_PROGRAMS = $(tpm2_simulator)
noinst_LIBRARIES = $(libplatform) $(libtpm)

TPMCmd_Platform_src_libplatform_a_CFLAGS = $(EXTRA_CFLAGS) $(PLATFORM_INC) \
    $(TPM_INC)
TPMCmd_Platform_src_libplatform_a_SOURCES = $(PLATFORM_C) $(PLATFORM_H)

TPMCmd_Simulator_src_tpm2_simulator_CFLAGS = $(EXTRA_CFLAGS) $(PLATFORM_INC) \
    $(TPM_INC) $(SIMULATOR_INC) $(LIBCRYPTO_CFLAGS) $(PTHREAD_CFLAGS)
# the weird / duplicate static library is necessary for dealing with the
# circular dependency beetween libplatform and libtpm
TPMCmd_Simulator_src_tpm2_simulator_LDADD = $(libplatform) $(libtpm) \
    $(libplatform) $(LIBCRYPTO_LIBS) $(PTHREAD_LIBS) @ADDITIONAL_LIBS@
TPMCmd_Simulator_src_tpm2_simulator_SOURCES = $(SIMULATOR_C) $(SIMULATOR_H)

TPMCmd_tpm_src_libtpm_a_CFLAGS = $(EXTRA_CFLAGS) $(PLATFORM_INC) $(TPM_INC) \
    $(LIBCRYPTO_CFLAGS)
TPMCmd_tpm_src_libtpm_a_SOURCES = $(TPM_C) $(TPM_H) $(PLATFORM_H)
