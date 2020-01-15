DIRS += $(BUILD)/tpm/src/command/NVStorage

tpm_src_command_NVStorage_SRCS = \
NV_ReadPublic.c \
NV_Certify.c \
NV_spt.c \
NV_ChangeAuth.c \
NV_Write.c \
NV_Read.c \
NV_ReadLock.c \
NV_GlobalWriteLock.c \
NV_Extend.c \
NV_SetBits.c \
NV_UndefineSpaceSpecial.c \
NV_DefineSpace.c \
NV_WriteLock.c \
NV_UndefineSpace.c \
NV_Increment.c \

SRC_LIST += $(foreach src,$(tpm_src_command_NVStorage_SRCS),tpm/src/command/NVStorage/$(src))
