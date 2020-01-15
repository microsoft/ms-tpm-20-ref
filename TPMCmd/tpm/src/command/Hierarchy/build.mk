DIRS += $(BUILD)/tpm/src/command/Hierarchy

tpm_src_command_Hierarchy_SRCS = \
CreatePrimary.c \
Clear.c \
ChangeEPS.c \
ClearControl.c \
ChangePPS.c \
SetPrimaryPolicy.c \
HierarchyControl.c \
HierarchyChangeAuth.c \

SRC_LIST += $(foreach src,$(tpm_src_command_Hierarchy_SRCS),tpm/src/command/Hierarchy/$(src))
