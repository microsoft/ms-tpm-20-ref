# Microsoft Reference Implementation for TPM 2.0
# Copyright (c) Microsoft Corporation
# This software is being made available under certain license terms, as detailed at
# https://github.com/microsoft/ms-tpm-20-ref/blob/main/LICENSE
#
# This demonstrates how to create a crypto library.  Ultimately, the Core Tpm
# library will expect 3 crypto libraries to be created, plus 3 related header
# libraries. They can all be created in a single CMakeLists.txt as demonstrated
# here, or separately.
#

# this built-in library expects the caller to point to OpenSSL includes and library paths
# before calling this script
if (WIN32)
    if (NOT OSSL_INCLUDE_SUBDIR)
        message(FATAL_ERROR "OSSL_INCLUDE_SUBDIR must be set when using Ossl on Win32. was [${OSSL_INCLUDE_SUBDIR}]")
    endif()
    if (NOT EXISTS "${OSSL_INCLUDE_SUBDIR}")
        message(FATAL_ERROR "OSSL_INCLUDE_SUBDIR must exist when using Ossl libraries; was [${OSSL_INCLUDE_SUBDIR}].")
    endif()
endif()

project(Tpm_Cryptolib_Ossl VERSION 1.0)
print_project_info()
# generate Tpm_Cryptolib_Ossl_Headers
add_subdirectory(include/Ossl)

# Library First: Tpm_CryptoLib_Math_<name>
# Library Second: Tpm_CryptoLib_Symmetric_<name>
# Library Third: Tpm_CryptoLib_Hash_<name>
add_library(Tpm_CryptoLib_Math_Ossl STATIC)
add_library(Tpm_CryptoLib_Math_Ossl::Tpm_CryptoLib_Math_Ossl ALIAS Tpm_CryptoLib_Math_Ossl)
add_library(Tpm_CryptoLib_Symmetric_Ossl ALIAS Tpm_CryptoLib_Math_Ossl)
add_library(Tpm_CryptoLib_Hash_Ossl ALIAS Tpm_CryptoLib_Math_Ossl)

# reference necessary includes from Tpm core library
target_link_libraries(Tpm_CryptoLib_Math_Ossl PUBLIC TpmConfiguration)
target_link_libraries(Tpm_CryptoLib_Math_Ossl PUBLIC Tpm_Public_Headers)
target_link_libraries(Tpm_CryptoLib_Math_Ossl PUBLIC Tpm_CryptoLib_TpmBigNum_Headers)

# get access to the private TPM headers directly so they don't show up in the
# usage attributes.  Using an INTERFACE library (Tpm_Private_Headers) doesn't allow
# private inheritance
target_include_directories(Tpm_CryptoLib_Math_Ossl PRIVATE
    ../../include
)

target_sources(Tpm_CryptoLib_Math_Ossl PRIVATE
    "BnToOsslMath.c"
    "TpmToOsslSupport.c"
)

# include files will be referenced relative to the <name>.
# for example, given this tree:
# C:\tpm\cryptolibs\Ossl
# │   BnToOsslMath.c
# │
# └───include (*)
#     └───Ossl
#             BnToOsslMath.h
#
# Then, the correct include directory for the project is the include folder
# marked with an (*)
target_include_directories(Tpm_CryptoLib_Math_Ossl PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (WIN32)

    cmake_path(RELATIVE_PATH OSSL_INCLUDE_SUBDIR
            BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE rel_ossl)

    cmake_path(ABSOLUTE_PATH rel_ossl
            BASE_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}
            OUTPUT_VARIABLE OSSL_INCLUDE_SUBDIR2
            )

    # don't provide the OpenSSL header directory on an INSTALL_INTERFACE basis.
    # if a component is consuming from an install environment, it needs to
    # provide a pointer to OpenSLL on Windows, and on Linux it's expected
    # to be installed in the system standard location.
    target_include_directories(Tpm_CryptoLib_Math_Ossl
                            PUBLIC
                            "$<BUILD_INTERFACE:${OSSL_INCLUDE_SUBDIR}>"
                            )
    target_link_libraries(Tpm_CryptoLib_Math_Ossl INTERFACE libcrypto)
else()
    find_package(OpenSSL 3.0.14 REQUIRED COMPONENTS Crypto)
    target_link_libraries(Tpm_CryptoLib_Math_Ossl PUBLIC OpenSSL::Crypto)
endif()

# create install and export information for downstream projects to use
install_and_export_config_targets(Tpm_CryptoLib_Math_Ossl)

##############################################################
# BEGIN --- install the header files provided by this project.
##############################################################
# nothing to do

# LAST: create the targets.cmake file for this package
export_targets_cmake_file(Tpm_CryptoLib_Math_Ossl)
