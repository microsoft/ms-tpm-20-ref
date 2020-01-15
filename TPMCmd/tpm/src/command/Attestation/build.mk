DIRS += $(BUILD)/tpm/src/command/Attestation

tpm_src_command_Attestation_SRCS = \
Attest_spt.c \
GetSessionAuditDigest.c \
CertifyX509.c \
GetTime.c \
GetCommandAuditDigest.c \
Certify.c \
CertifyCreation.c \
Quote.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Attestation_SRCS),tpm/src/command/Attestation/$(src))
