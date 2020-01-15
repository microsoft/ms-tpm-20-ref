DIRS += $(BUILD)/tpm/src/command/Misc

tpm_src_command_Misc_SRCS = \
PP_Commands.c \
SetAlgorithmSet.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Misc_SRCS),tpm/src/command/Misc/$(src))
