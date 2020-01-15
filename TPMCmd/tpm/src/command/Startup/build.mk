DIRS += $(BUILD)/tpm/src/command/Startup

tpm_src_command_Startup_SRCS = \
Shutdown.c \
Startup.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Startup_SRCS),tpm/src/command/Startup/$(src))
