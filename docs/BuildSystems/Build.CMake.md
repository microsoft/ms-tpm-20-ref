# CMake Build System - TPM2 Reference Library

- [CMake Build System - TPM2 Reference Library](#cmake-build-system---tpm2-reference-library)
  - [- 32-bit Windows + OpenSSL](#--32-bit-windows--openssl)
- [Quick Start](#quick-start)
- [Build Domains](#build-domains)
- [Library Only Builds](#library-only-builds)
  - [Build Domain #1 - TPM Core Library](#build-domain-1---tpm-core-library)
  - [Build Domain #2 - TPM Platform Library](#build-domain-2---tpm-platform-library)
  - [Build Domain #3 - TPM Application](#build-domain-3---tpm-application)
  - [Consuming TPM CoreLib outside CMake](#consuming-tpm-corelib-outside-cmake)
  - [More Info](#more-info)
- [Known Issues](#known-issues)
- [Prerequisites](#prerequisites)
  - [Install CMake & put it on your path](#install-cmake--put-it-on-your-path)
  - [Obtain the Crypto library of your choice](#obtain-the-crypto-library-of-your-choice)
- [Selected Examples](#selected-examples)
  - [32-bit Windows + OpenSSL](#32-bit-windows--openssl)
---

NOTE: ** CMake support is experimental and does not yet support Linux. **

These instructions are under development and subject to change.

Note: TPM Requires CMake 3.16.3 or later.
# Quick Start

See [CMake Quick Start](Build.CMake.QuickStart.md)

# Build Domains

This repository uses the concept of "Build Domains" to separate different CMake
components that should be built separately. This is, the three CMake steps (Generate,
Build, Install) should be run on one Build Domain before using the results in another
Build Domain.

The Reference Code supports two configurations of Build Domains.  The simplest system
uses a single Build Domain (that is a single set of Generate, Build, Install).  This
is the default behavior of the `TPMCmd/CMakeLists.txt` file.

# Library Only Builds

`TPMCmd/CMakeLists.txt` supports an optional configuration that does not include
the platform library or the simulator app.  This configuration uses three
build domains to construct the Simulator.  Each CMake generate call is run on
 a different directory as indicated below, but share the same `--install-prefix`
 so the components for each step is available to be found by the next step.

## Build Domain #1 - TPM Core Library

The `TPM Core Library` build domain builds a complete TPM library implementation,
including Configuration options and all crypto support. This build domain is
represented by `TPMCmd/CMakeLists.txt` when the CMake is given the optional define
`-D Tpm_BuildOption_LibOnly=1` during the generate phase.

## Build Domain #2 - TPM Platform Library

The `TPM Platform Library` build domain consumes the Core Library install tree, and
produces the platform library and adds its components to the install tree.

This build domain is represented by `TPMCmd/Platform/CMakeLists.txt` when CMake is run
directly on the Platform folder.

## Build Domain #3 - TPM Application

The TPM Simulator build domain consumes both combined Core Library and Platform
install tree, and produces the final simulator and installs it to the `bin/` folder of
the install tree.

This build domain is represented by `TPMCmd/Simulator/CMakeLists.txt` when CMake is
run directly on the Platform folder.

## Consuming TPM CoreLib outside CMake

It is possible to consume the `TPM Core Library` without CMake by consuming the
headers and libraries from the install tree created by CMake.  The instructions will
be specific to the downstream build tree and are left as an exercise for the reader.

## More Info

The `scripts/cmake_*.cmd` files as well as the various CMakeLists.txt files contain
more documentation.

# Known Issues

1. Does not search for external packages (e.g. OpenSSL).
2. Build failure with wolf crypto libraries.

# Prerequisites

## Install CMake & put it on your path

This is performed in an OS specific way, possibilities include:
* using apt-get on Linux,
* Installing the MSI or Zip version of CMake directly from [CMake.org](https://cmake.org/download/)
* Using the CMake tools from a Visual Studio Installation

## Obtain the Crypto library of your choice

Follow the relevant [Build Instructions](BuildIntro.md#build-instructions)
to install a [supported crypto library](BuildIntro.md#supported-crypto-libraries)
for your OS.

For Windows: Use `getossl.cmd` to copy the contents of an unzipped downloaded copy of OpenSSL
before configuring with CMake:

Before configuring a build targeting 32-bit Windows:
```
scripts\getossl.cmd x86 path\to\downloaded\openssl-1.1.1n\openssl-1.1\x86
```

Before configuring a build targeting 64-bit Windows:
```
scripts\getossl.cmd x64 path\to\downloaded\openssl-1.1.1n\openssl-1.1\x64
```

# Selected Examples

## Visual Studio Code

[Visual Studio Code](https://code.visualstudio.com/) has support for CMake built in, so we can use it to build
the simulator. These instructions even work via
[VSCode Remote](https://code.visualstudio.com/docs/remote/remote-overview). You will still need a C compiler,
such as the one included in [Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/).

### Select a kit (compiler)

Open the Command Palette (Ctrl + Shift + P) and search for `CMake: Select a Kit`. Choose your compiler there.

### Configure

Open the Command Palette (Ctrl + Shift + P) and search for `CMake: Configure`. This should take a few seconds, and then output something like:

```
[cmake] -- Build files have been written to: C:/Users/.../src/TPM-Internal/build
[visual-studio] Patch Windows SDK path from C:\Program Files (x86)\Windows Kits\10\bin\x86 to C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x86 for C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat
```

### Build

Open the Command Palette (Ctrl + Shift + P) and search for `CMake: Build`. This should take a few minutes, and then output something like:

```
...
[build]   Marshal.c
[build]   MathOnByteBuffers.c
[build]   Memory.c
[build]   Power.c
[build]   PropertyCap.c
[build]   Response.c
[build]   ResponseCodeProcessing.c
[build]   TableDrivenMarshal.c
[build]   TableMarshalData.c
[build]   TpmFail.c
[build]   TpmSizeChecks.c
[build]   Generating Code...
[build]   Tpm_CoreLib.vcxproj -> C:\Users\...\src\TPM-Internal\build\tpm\src\Debug\Tpm_CoreLib.lib
[build]   TcpServer.c
[build]   Simulator.vcxproj -> C:\Users\...\src\TPM-Internal\build\Simulator\Debug\Simulator.exe
[build] Build finished with exit code 0
```

## 32-bit Windows + OpenSSL using command-line cmake

1. Change to the TPMCmd directory.
2. Run the appropriate Visual Studio commands to set the environment variables for a 32bit build.  For example:
```
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
```
3. Setup the CMake build environment
```
cmake -S . -B DebugOpenSSL32 -G "Visual Studio 16 2019" -T v141 -A Win32
```
This tells CMake to set the top level of the Source tree to TPMCmd/ and create a Build
directory "TPMCmd/DebugOpenSSL32/"

4. Execute the build
Instruct CMake to build the build environment just created.
```
cmake --build DebugOpenSSL32
```

If everything went well, you should have a working Simulator.exe in:
`TPMCmd\DebugOpenSSL32\install\bin\Simulator.exe`

## Linux + OpenSSL using command-line cmake

1. Install cmake, gcc and openssl using the linux distribution package manager.
2. Setup the CMake build environment
```
cmake -S TPMCmd/. -B TPMCmd/build/.
```
This tells CMake to set the top level of the Source tree to TPMCmd/ and create a Build
directory "TPMCmd/build/"

4. Execute the build
Instruct CMake to build the build environment just created.
```
cmake --build TPMCmd/build/.
```

If everything went well, you should have a working binary in:
`TPMCmd\build\Simulator`
