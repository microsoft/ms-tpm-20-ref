# Official TPM 2.0 Reference Implementation (by Microsoft) #

[![Build Status](https://travis-ci.org/Microsoft/ms-tpm-20-ref.svg?branch=master)](https://travis-ci.org/Microsoft/ms-tpm-20-ref)

This is the official TCG reference implementation of the [TPM 2.0 Specification](https://trustedcomputinggroup.org/tpm-library-specification). The project contains complete source code of the reference implementation with a Microsoft Visual Studio solution and Linux autotools build scripts.

See the definition of the `SPEC_VERSION`, `SPEC_YEAR` and `SPEC_DAY_OF_YEAR` values in the [TpmTypes.h](TPMCmd/tpm/include/TpmTypes.h) header for the exact revision/date of the TPM 2.0 specification, which the given source tree snapshot corresponds to.

The reference implementation can be directly used via the [TPM 2.0 simulator](TPMCmd/Simulator) that emulates a TPM 2.0 device and can be accessed via a custom TCP based protocol. The simplest way to work with the simulator is to use a [TSS library](https://github.com/Microsoft/TSS.MSR) for the programming language of your choice - C#/.Net, C++, Java, Python, JavaScript/Node.js are currently supported. The C language TSS implementing the TCG's TSS API specifiaction is available [here](https://github.com/tpm2-software/tpm2-tss).

## Visual Studio build ##

Before building the Visual Studio solution:

* Setup one or both of the following underlying cryptographic libraries:

   ### OpenSSL library ###

   1. Create `TPMCmd/lib` folder and place a static OpenSSL library (`libcrypto.lib`) built for the `x86` architecture there. For the `x64` architecture use the `TPMCmd/lib/x64` folder.

        The static libs can be either static libraries proper, or import libraries accompanying the corresponding DLLs. In the latter case you'll need to ensure that ther is a matching copy of the OpenSSL DLL in the standard Windows search path, so that it is available when you run the simulator executable (e.g. copy it into the same folder where `simulator.exe` is located).

        Recommended version of OpenSSL is `1.1.1d` or higher.

   2. Create `TPMCmd/OsslInclude/openssl` folder and copy there the contents of the `openssl/include/openssl` folder in the OpenSSL source tree used to build the OpenSSL library.

      If you do not disable SM{2,3,4} algorithms support either while building OpenSSL or in the simulator (see the Linux section below), the build may fail because of missing SM{2,3,4}.h headers, which is the result of an apparent bug/misconfiguration in the OpenSSL build tree/scrips. In this case you may also need to copy over the SM{2,3,4}.h headers from OpenSSL’s `include/crypt` folder.

   3. Build the solution with either Debug or Release as the active configuration.

   ### Wolfcrypt library (wolfSSL) ###

   1. WolfSSL is included as a submodule. Initialize and update the submodule to fetch the project and checkout the appropriate commit.

        > git submodule init
        > git submodule update

        The current commit will point the minimum recommended version of wolfSSL. Moving to a more recent tag or commit should also be supported but might not be tested. 

   2. Build the solution with either WolfDebug or WolfRelease as the active configuration, either from inside the Visual Studio or with the following command line:

        > msbuild TPMCmd\simulator.sln /p:Configuration=WolfDebug

* If necessary, update the definitions of the following macros in the [VendorString.h](TPMCmd/tpm/include/VendorString.h) header: `MANUFACTURER`, `VENDOR_STRING_1`, `FIRMWARE_V1 and FIRMWARE_V2`

## Linux build

Follows the common `./bootstrap && ./configure && make` convention.

Note that autotools scripts require the following prerequisite packages: `autoconf-archive`, `pkg-config`, and sometimes `build-essential` and `automake`. Their absence is not automatically detected. The build also needs `gcc` and `libssl-dev` packages.

In some Linux configurations linking may fail because of SM{2,3,4} routines missing in the the OpenSSL library. This is a bug in the OpenSSL configuration, as it is supposed to support SM algs since its initial 1.1.1 revision, and when it is built without them, its `opensslconf.h` has to define OPENSSL_NO_SM{2,3,4} macros. However, these macros are (or were) not defined in many official OpenSSL packages (such as libssl-dev). If you have this issue then several options exist:
- Disable SM algorithms in `TpmProfile.h`  (set `ALG_SM2`, `ALG_SM3_256`, `ALG_SM4` to `ALG_NO`);
- Manually define `OPENSSL_NO_SM2`, `OPENSSL_NO_SM3`, `OPENSSL_NO_SM4` in `opensslconf.h`;
- Use a custom buit OpenSSL library.
