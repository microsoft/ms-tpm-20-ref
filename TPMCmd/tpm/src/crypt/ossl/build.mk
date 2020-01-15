DIRS += $(BUILD)/tpm/src/crypt/ossl

tpm_src_crypt_ossl_SRCS = \
TpmToOsslSupport.c \
TpmToOsslDesSupport.c \
TpmToOsslMath.c \

SRC_LIST += $(foreach src,$(tpm_src_crypt_ossl_SRCS),tpm/src/crypt/ossl/$(src))
