DIRS += $(BUILD)/tpm/src/command/FieldUpgrade

tpm_src_command_FieldUpgrade_SRCS = \
FieldUpgradeStart.c \
FieldUpgradeData.c \
FirmwareRead.c \

SRC_LIST += $(foreach src,$(tpm_src_command_FieldUpgrade_SRCS),tpm/src/command/FieldUpgrade/$(src))
