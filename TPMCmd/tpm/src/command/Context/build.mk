DIRS += $(BUILD)/tpm/src/command/Context

tpm_src_command_Context_SRCS = \
EvictControl.c \
Context_spt.c \
ContextSave.c \
FlushContext.c \
ContextLoad.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Context_SRCS),tpm/src/command/Context/$(src))
