
DIRS =
BUILD ?= ../build
CC ?= gcc
AR ?= ar

TPM2_LIB = $(BUILD)/libtpm2.a

ifeq ($V,1)
Q=
else
Q=@
endif

DEFINES = VERSION=\"0.1\" HASH_LIB=Ossl SYM_LIB=Ossl MATH_LIB=Ossl
FLAGS = stack-protector-all PIC
WARNINGS =  error all format-security
WARNINGS_NO_ERROR = empty-body expansion-to-defined parentheses \
	pointer-to-int-cast missing-braces unused-result
INCLUDES = . Platform/include Platform/include/prototypes tpm/include \
	tpm/include/prototypes

CFLAGS = $(foreach d,$(DEFINES),-D$(d) )\
	$(foreach f,$(FLAGS),-f$(f) )\
	$(foreach w,$(WARNINGS),-W$(w) )\
	$(foreach w,$(WARNINGS_NO_ERROR),-Wno-error=$(w) )\
	$(foreach i,$(INCLUDES),-I$(i) )

ifeq ($(DEBUG),1)
CLFAGS += -O0 -g
else
CFLAGS += -O2
endif

CFLAGS += -std=gnu11

all: $(TPM2_LIB)

include ./tpm/src/support/build.mk
include ./tpm/src/command/Hierarchy/build.mk
include ./tpm/src/command/HashHMAC/build.mk
include ./tpm/src/command/Vendor/build.mk
include ./tpm/src/command/AttachedComponent/build.mk
include ./tpm/src/command/Random/build.mk
include ./tpm/src/command/FieldUpgrade/build.mk
include ./tpm/src/command/Testing/build.mk
include ./tpm/src/command/Duplication/build.mk
include ./tpm/src/command/Asymmetric/build.mk
include ./tpm/src/command/Signature/build.mk
include ./tpm/src/command/Object/build.mk
include ./tpm/src/command/Ecdaa/build.mk
include ./tpm/src/command/NVStorage/build.mk
include ./tpm/src/command/Attestation/build.mk
include ./tpm/src/command/Misc/build.mk
include ./tpm/src/command/ClockTimer/build.mk
include ./tpm/src/command/DA/build.mk
include ./tpm/src/command/CommandAudit/build.mk
include ./tpm/src/command/Context/build.mk
include ./tpm/src/command/Symmetric/build.mk
include ./tpm/src/command/Session/build.mk
include ./tpm/src/command/EA/build.mk
include ./tpm/src/command/Startup/build.mk
include ./tpm/src/command/PCR/build.mk
include ./tpm/src/command/Capability/build.mk
include ./tpm/src/main/build.mk
include ./tpm/src/X509/build.mk
include ./tpm/src/subsystem/build.mk
include ./tpm/src/crypt/ltc/build.mk
include ./tpm/src/crypt/ossl/build.mk
include ./tpm/src/crypt/wolf/build.mk
include ./tpm/src/crypt/build.mk
include ./tpm/src/events/build.mk

OBJS := $(patsubst %.c,%.o,$(addprefix $(BUILD)/,$(SRC_LIST)))
DEPS := $(addsuffix .d,$(OBJS))

-include $(DEPS)

$(DIRS):
	$Q[ -d $@ ] || mkdir -p $@

$(TPM2_LIB): $(OBJS)
	@[ -s $Q ] || echo "    AR $<"
	$Qrm -f $@
	$Q$(AR) crD $@ $^

$(BUILD)/%.o: %.c  | $(DIRS)
	@[ -s $Q ] || echo "    CC $<"
	$Q$(CC) $(CFLAGS) -MMD -MT $@ -MF ${@}.d -o $@ -c $<

clean:
	$Qrm -rf $(BUILD)
