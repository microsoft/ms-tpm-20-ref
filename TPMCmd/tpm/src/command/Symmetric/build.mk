DIRS += $(BUILD)/tpm/src/command/Symmetric

tpm_src_command_Symmetric_SRCS = \
HMAC.c \
MAC.c \
EncryptDecrypt_spt.c \
Hash.c \
EncryptDecrypt.c \
EncryptDecrypt2.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Symmetric_SRCS),tpm/src/command/Symmetric/$(src))
