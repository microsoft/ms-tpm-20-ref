DIRS += $(BUILD)/tpm/src/command/Signature

tpm_src_command_Signature_SRCS = \
Sign.c \
VerifySignature.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Signature_SRCS),tpm/src/command/Signature/$(src))
