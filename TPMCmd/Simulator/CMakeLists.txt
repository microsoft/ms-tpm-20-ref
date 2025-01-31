# Microsoft Reference Implementation for TPM 2.0
# Copyright (c) Microsoft Corporation
# This software is being made available under certain license terms, as detailed at
# https://github.com/microsoft/ms-tpm-20-ref/blob/main/LICENSE
#
cmake_minimum_required(VERSION 3.16.3)
include(${CMAKE_CURRENT_SOURCE_DIR}/../tpm/cmake/tpm_support.cmake)

project(Simulator)
print_project_info()

set(CMAKE_CONFIGURATION_TYPES "Debug"
    CACHE STRING "Configuration types" FORCE)

# use standard output directories.  Expected by package_utilities
include(GNUInstallDirs)

add_executable(Simulator
    src/TcpServer.c
    src/TPMCmdp.c
    src/TPMCmds.c
)

# Additional include directories
# simulator folders
target_include_directories(Simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include;
    ${CMAKE_CURRENT_SOURCE_DIR}/include/prototypes;
)

# Preprocessor definitions
target_compile_definitions(Simulator PRIVATE
    _UNICODE
    _CONSOLE
    _DIAGNOSTICS
)


# Only call find_package if this CMakeLists file is not being included via
# add_subdirectory.  Calling find_package during add_subdirectory will cause the
# REQUIRED clause of the find_pacakge to fail since they haven't been built
# yet.)
if(PROJECT_IS_TOP_LEVEL)
    # External libs and include directories
    find_package(Tpm_CompilerOptions PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(TpmConfiguration CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_Public_Headers CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_Platform_Interface CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_PlatformLib CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_CryptoLib_Common PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_CryptoLib_TpmBigNum_Headers PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_CryptoLib_Math_Ossl CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_CryptoLib_TpmBigNum CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
    find_package(Tpm_CoreLib CONFIG REQUIRED PATHS ${CMAKE_INSTALL_PREFIX} NO_DEFAULT_PATH )
endif()


if(WIN32)
    # Link libraries
    target_link_libraries(Simulator PUBLIC TpmConfiguration::TpmConfiguration)
    target_link_libraries(Simulator PUBLIC Tpm_Public_Headers::Tpm_Public_Headers)
    target_link_libraries(Simulator PUBLIC Tpm_PlatformLib::Tpm_PlatformLib)
    target_link_libraries(Simulator PUBLIC Tpm_Platform_Interface::Tpm_Platform_Interface)
    target_link_libraries(Simulator PUBLIC Tpm_CoreLib::Tpm_CoreLib)
    target_link_libraries(Simulator PUBLIC Tpm_CryptoLib_TpmBigNum::Tpm_CryptoLib_TpmBigNum)

    set(WIN_LIBCRYPTO_PATH)
    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        set(WIN_LIBCRYPTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib/x64")
        set(source_filename libcrypto-1_1-x64.dll)
    elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
        set(WIN_LIBCRYPTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
        set(source_filename libcrypto-1_1.dll)
    else()
        message(FATAL_ERROR "CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
    endif()

    target_link_libraries(Simulator PRIVATE
        Ws2_32.lib
        Rpcrt4.lib
    )

    target_link_directories(Simulator PRIVATE ${WIN_LIBCRYPTO_PATH})

    # copy the openssl dll to simulator output folder if TPM is using openssl.
    # only necessary on WIN32.
    message(DEBUG "adding target to copy ${WIN_LIBCRYPTO_PATH}/${source_filename} to simulator folder")

    # target must be included in ALL or it won't be built by default
    # since the direction of the dependency is simulator->copy,
    # specifying DEPENDS here doesn't include the copy if simulator is built, but
    # would build Simulator if --target copy_libcrypto_dll is built first.
    add_custom_target(copy_libcrypto_dll ALL
        COMMAND ${CMAKE_COMMAND} -E
            copy ${WIN_LIBCRYPTO_PATH}/${source_filename} $<TARGET_FILE_DIR:Simulator>/${source_filename}
        )

    install(FILES ${WIN_LIBCRYPTO_PATH}/${source_filename}
            DESTINATION ${CMAKE_INSTALL_BINDIR})

else()
  # Link libraries
  target_link_libraries(Simulator PUBLIC
    -Wl,--start-group
    TpmConfiguration::TpmConfiguration
    Tpm_Public_Headers::Tpm_Public_Headers
    Tpm_CryptoLib_TpmBigNum::Tpm_CryptoLib_TpmBigNum
    Tpm_CoreLib::Tpm_CoreLib
    Tpm_PlatformLib::Tpm_PlatformLib
    Tpm_Platform_Interface::Tpm_Platform_Interface
    -Wl,--end-group
  )
endif ()

# include Simulator
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
