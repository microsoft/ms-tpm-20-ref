DIRS += $(BUILD)/tpm/src/X509

tpm_src_X509_SRCS = \
X509_ECC.c \
TpmASN1.c \
X509_spt.c \
X509_RSA.c \

SRC_LIST += $(foreach src,$(tpm_src_X509_SRCS),tpm/src/X509/$(src))
