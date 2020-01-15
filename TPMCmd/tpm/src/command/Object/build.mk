DIRS += $(BUILD)/tpm/src/command/Object

tpm_src_command_Object_SRCS = \
Unseal.c \
Object_spt.c \
LoadExternal.c \
ActivateCredential.c \
MakeCredential.c \
CreateLoaded.c \
ReadPublic.c \
Create.c \
Load.c \
ObjectChangeAuth.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Object_SRCS),tpm/src/command/Object/$(src))
