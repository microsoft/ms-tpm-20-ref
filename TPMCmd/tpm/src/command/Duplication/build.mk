DIRS += $(BUILD)/tpm/src/command/Duplication

tpm_src_command_Duplication_SRCS = \
Import.c \
Duplicate.c \
Rewrap.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Duplication_SRCS),tpm/src/command/Duplication/$(src))
