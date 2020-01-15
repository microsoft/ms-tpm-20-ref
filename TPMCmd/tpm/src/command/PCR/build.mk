DIRS += $(BUILD)/tpm/src/command/PCR

tpm_src_command_PCR_SRCS = \
PCR_Event.c \
PCR_SetAuthPolicy.c \
PCR_Read.c \
PCR_Allocate.c \
PCR_SetAuthValue.c \
PCR_Reset.c \
PCR_Extend.c \

SRC_LIST += $(foreach src,$(tpm_src_command_PCR_SRCS),tpm/src/command/PCR/$(src))
