DIRS += $(BUILD)/tpm/src/command/Testing

tpm_src_command_Testing_SRCS = \
SelfTest.c \
GetTestResult.c \
IncrementalSelfTest.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Testing_SRCS),tpm/src/command/Testing/$(src))
