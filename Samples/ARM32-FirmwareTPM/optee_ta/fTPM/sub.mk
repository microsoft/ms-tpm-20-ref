WARNS ?= 1
NOWERROR ?= 1
CFG_TA_DEBUG ?= 1
CFG_TEE_TA_LOG_LEVEL ?= 1

cflags-y += -DTHIRTY_TWO_BIT -DCFG_TEE_TA_LOG_LEVEL=$(CFG_TEE_TA_LOG_LEVEL) -D_ARM_ -w -Wno-strict-prototypes -mcpu=$(TA_CPU) -fstack-protector -Wstack-protector

ifeq ($(CFG_ARM64_ta_arm64),y)
cflags-y += -mstrict-align
else
cflags-y += -mno-unaligned-access
endif

ifeq ($(CFG_TA_DEBUG),y)
cflags-y += -DfTPMDebug=1
cflags-y += -DDBG=1
cflags-y += -O0
cflags-y += -DDEBUG
else
cflags-y += -Os
cflags-y += -DNDEBUG
endif

#
# Link the required external code into the libraries folder. OP-TEE build
# does not work well when accessing anything below the root directory. Use
# symlinks to trick it.
#
all: create_lib_symlinks
clean: clean_lib_symlinks

subdirs-y += lib

global-incdirs-y += include
global-incdirs-y += reference/include
global-incdirs-y += platform/include

srcs-y += platform/AdminPPI.c
srcs-y += platform/Cancel.c
srcs-y += platform/Clock.c
srcs-y += platform/Entropy.c
srcs-y += platform/LocalityPlat.c
srcs-y += platform/NvAdmin.c
srcs-y += platform/NVMem.c
srcs-y += platform/PowerPlat.c
srcs-y += platform/PlatformData.c
srcs-y += platform/PPPlat.c
srcs-y += platform/RunCommand.c
srcs-y += platform/Unique.c
srcs-y += platform/EPS.c
srcs-y += reference/RuntimeSupport.c

srcs-y += fTPM.c
