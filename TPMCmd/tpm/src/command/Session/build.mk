DIRS += $(BUILD)/tpm/src/command/Session

tpm_src_command_Session_SRCS = \
StartAuthSession.c \
PolicyRestart.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Session_SRCS),tpm/src/command/Session/$(src))
