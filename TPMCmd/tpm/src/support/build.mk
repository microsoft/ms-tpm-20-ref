DIRS += $(BUILD)/tpm/src/support

tpm_src_support_SRCS = \
MathOnByteBuffers.c \
Bits.c \
Memory.c \
CommandCodeAttributes.c \
Entity.c \
TableDrivenMarshal.c \
TpmSizeChecks.c \
Manufacture.c \
IoBuffers.c \
ResponseCodeProcessing.c \
Handle.c \
PropertyCap.c \
TableMarshalData.c \
Response.c \
Global.c \
Marshal.c \
TpmFail.c \
Locality.c \
Power.c \
AlgorithmCap.c \

SRC_LIST += $(foreach src,$(tpm_src_support_SRCS),tpm/src/support/$(src))
