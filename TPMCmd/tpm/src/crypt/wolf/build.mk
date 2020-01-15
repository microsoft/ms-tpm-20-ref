DIRS += $(BUILD)/tpm/src/crypt/wolf

tpm_src_crypt_wolf_SRCS = \
TpmToWolfSupport.c \
TpmToWolfMath.c \
TpmToWolfDesSupport.c \

SRC_LIST += $(foreach src,$(tpm_src_crypt_wolf_SRCS),tpm/src/crypt/wolf/$(src))
