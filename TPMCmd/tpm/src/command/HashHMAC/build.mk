DIRS += $(BUILD)/tpm/src/command/HashHMAC

tpm_src_command_HashHMAC_SRCS = \
SequenceUpdate.c \
MAC_Start.c \
EventSequenceComplete.c \
SequenceComplete.c \
HashSequenceStart.c \
HMAC_Start.c \

SRC_LIST += $(foreach src,$(tpm_src_command_HashHMAC_SRCS),tpm/src/command/HashHMAC/$(src))
