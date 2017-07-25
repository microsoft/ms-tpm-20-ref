This is a Microsoft Visual Studio solution that contains reference implementation of the TPM 2.0 Specification by TCG available at https://trustedcomputinggroup.org/tpm-library-specification.

See the TPMCmd/tpm/include/TpmTypes.h header for the exact revision/date of the TPM 2.0 specification issue, which the given source tree snapshot corresponds to.

Before building the solution:

1) Uncomment and update the definitions of the following macros in the TPMCmd/tpm/include/VendorString.h header:
   - MANUFACTURER
   - VENDOR_STRING_1
   - FIRMWARE_V1 and FIRMWARE_V2
   
2) Create TPMCmd/lib folder and place a static OpenSSL library (libeay32.lib or libcrypto.lib) there. This may be either complete static library, or import library accompanying the corresponding DLL. In the latter case you'll need to copy the OpenSSL DLL into the standard Windows search path, so that it was available when you run the simulator executable (e.g. copy it into the same folder where simulator.exe is located).
   
   If you use libcrypto.lib, you'll need to either update "Linker|Input|Additional Dependencies" property of the Tpm project in the simulator solution or, alternatively, rename libcrypto.lib to libeay32.lib.
   
   Recommended version of OpenSSL is 1.0.2d or higher.

3) Create TPMCmd/OsslInclude/openssl folder and copy there the contents of the openssl/include/openssl folder of the OpenSSL source tree used to build the static library used on the step 2).

   If you use OpenSSL 1.1, you'll additionally need to:
   - Copy the openssl/crypto/bn/bn_lcl.h header to the TPMCmd/OsslInclude/openssl folder;
   - Create TPMCmd/OsslInclude/openssl/internal folder and copy there the contents of the openssl/crypto/include/internal folder (do not confuse it with the openssl/include/internal folder that need not be copied).
