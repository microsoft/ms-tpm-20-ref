DIRS += $(BUILD)/tpm/src/command/CommandAudit

tpm_src_command_CommandAudit_SRCS = \
SetCommandCodeAuditStatus.c \

SRC_LIST += $(foreach src,$(tpm_src_command_CommandAudit_SRCS),tpm/src/command/CommandAudit/$(src))
