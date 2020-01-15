DIRS += $(BUILD)/tpm/src/command/AttachedComponent

tpm_src_command_AttachedComponent_SRCS = \
AC_GetCapability.c \
AC_Send.c \
AC_spt.c \
Policy_AC_SendSelect.c \

SRC_LIST += $(foreach src,$(tpm_src_command_AttachedComponent_SRCS),tpm/src/command/AttachedComponent/$(src))
