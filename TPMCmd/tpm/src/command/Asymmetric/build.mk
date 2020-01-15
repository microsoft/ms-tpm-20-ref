DIRS += $(BUILD)/tpm/src/command/Asymmetric

tpm_src_command_Asymmetric_SRCS = \
RSA_Decrypt.c \
RSA_Encrypt.c \
ECDH_KeyGen.c \
ECDH_ZGen.c \
EC_Ephemeral.c \
ZGen_2Phase.c \
ECC_Parameters.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Asymmetric_SRCS),tpm/src/command/Asymmetric/$(src))
