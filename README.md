This is a Microsoft Visual Studio solution that contains reference implementation of the TPM 2.0 Specification by TCG (https://trustedcomputinggroup.org/tpm-library-specification/).

See TPMCmd/tpm/include/TpmTypes.h for the exact revision/date of the TPM 2.0 specification issue, which the given source tree snapshot corresponds to.

Before building the solution:

1) Create TPMCmd/lib folder and place a static OpenSSL library (libeay32.lib) there. Recommended version is 1.0.2d or higher.

2) Create TPMCmd/OsslInclude/openssl folder and copy there the contents of the include/openssl folder of the OpenSSL source tree used to build the static library used on the step 1).

3) Uncomment and update the definitions of the following macros in the TPMCmd/tpm/include/VendorString.h header:
   - MANUFACTURER
   - VENDOR_STRING_1
   - FIRMWARE_V1 and FIRMWARE_V2
