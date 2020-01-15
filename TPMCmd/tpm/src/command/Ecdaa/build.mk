DIRS += $(BUILD)/tpm/src/command/Ecdaa

tpm_src_command_Ecdaa_SRCS = \
Commit.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Ecdaa_SRCS),tpm/src/command/Ecdaa/$(src))
