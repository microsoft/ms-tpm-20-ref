DIRS += $(BUILD)/tpm/src/events

tpm_src_events_SRCS = \
_TPM_Init.c \
_TPM_Hash_Start.c \
_TPM_Hash_Data.c \
_TPM_Hash_End.c \

SRC_LIST += $(foreach src,$(tpm_src_events_SRCS),tpm/src/events/$(src))
