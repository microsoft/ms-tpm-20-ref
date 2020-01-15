DIRS += $(BUILD)/tpm/src/crypt/ltc

tpm_src_crypt_ltc_SRCS = \
TpmToLtcDesSupport.c \
TpmToLtcSupport.c \
TpmToLtcMath.c \

SRC_LIST += $(foreach src,$(tpm_src_crypt_ltc_SRCS),tpm/src/crypt/ltc/$(src))
