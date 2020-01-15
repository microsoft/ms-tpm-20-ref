DIRS += $(BUILD)/tpm/src/command/EA

tpm_src_command_EA_SRCS = \
PolicyTemplate.c \
PolicyAuthorizeNV.c \
PolicyTicket.c \
PolicyPhysicalPresence.c \
PolicySecret.c \
PolicySigned.c \
PolicyPCR.c \
PolicyNV.c \
PolicyCpHash.c \
PolicyOR.c \
PolicyDuplicationSelect.c \
PolicyGetDigest.c \
Policy_spt.c \
PolicyCommandCode.c \
PolicyAuthValue.c \
PolicyAuthorize.c \
PolicyPassword.c \
PolicyNvWritten.c \
PolicyNameHash.c \
PolicyCounterTimer.c \
PolicyLocality.c \

SRC_LIST += $(foreach src,$(tpm_src_command_EA_SRCS),tpm/src/command/EA/$(src))
