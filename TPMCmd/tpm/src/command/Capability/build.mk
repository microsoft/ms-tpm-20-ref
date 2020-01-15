DIRS += $(BUILD)/tpm/src/command/Capability

tpm_src_command_Capability_SRCS = \
GetCapability.c \
TestParms.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Capability_SRCS),tpm/src/command/Capability/$(src))
