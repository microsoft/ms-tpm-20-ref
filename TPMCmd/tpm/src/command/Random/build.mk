DIRS += $(BUILD)/tpm/src/command/Random

tpm_src_command_Random_SRCS = \
GetRandom.c \
StirRandom.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Random_SRCS),tpm/src/command/Random/$(src))
