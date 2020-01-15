DIRS += $(BUILD)/tpm/src/crypt

tpm_src_crypt_SRCS = \
BnMath.c \
CryptEccMain.c \
CryptEccData.c \
CryptRand.c \
Ticket.c \
RsaKeyCache.c \
BnConvert.c \
CryptDes.c \
CryptHash.c \
PrimeData.c \
CryptUtil.c \
CryptEccKeyExchange.c \
CryptPrimeSieve.c \
CryptSym.c \
CryptSmac.c \
BnMemory.c \
CryptCmac.c \
CryptEccSignature.c \
CryptSelfTest.c \
CryptPrime.c \
AlgorithmTests.c \
CryptRsa.c \

SRC_LIST += $(foreach src,$(tpm_src_crypt_SRCS),tpm/src/crypt/$(src))
