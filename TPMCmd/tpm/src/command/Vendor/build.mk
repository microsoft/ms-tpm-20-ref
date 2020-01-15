DIRS += $(BUILD)/tpm/src/command/Vendor

tpm_src_command_Vendor_SRCS = \
Vendor_TCG_Test.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Vendor_SRCS),tpm/src/command/Vendor/$(src))
