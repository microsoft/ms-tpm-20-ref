DIRS += $(BUILD)/tpm/src/command/DA

tpm_src_command_DA_SRCS = \
DictionaryAttackParameters.c \
DictionaryAttackLockReset.c \

SRC_LIST += $(foreach src,$(tpm_src_command_DA_SRCS),tpm/src/command/DA/$(src))
