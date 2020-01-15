DIRS += $(BUILD)/tpm/src/subsystem

tpm_src_subsystem_SRCS = \
Session.c \
Object.c \
NvDynamic.c \
DA.c \
Time.c \
CommandAudit.c \
PP.c \
NvReserved.c \
Hierarchy.c \
PCR.c \

SRC_LIST += $(foreach src,$(tpm_src_subsystem_SRCS),tpm/src/subsystem/$(src))
