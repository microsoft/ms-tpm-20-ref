DIRS += $(BUILD)/tpm/src/main

tpm_src_main_SRCS = \
SessionProcess.c \
ExecCommand.c \
CommandDispatcher.c \

SRC_LIST += $(foreach src,$(tpm_src_main_SRCS),tpm/src/main/$(src))
