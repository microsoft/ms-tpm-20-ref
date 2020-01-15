DIRS += $(BUILD)/tpm/src/command/ClockTimer

tpm_src_command_ClockTimer_SRCS = \
ACT_SetTimeout.c \
ACT_spt.c \
ClockSet.c \
ClockRateAdjust.c \
ReadClock.c \

SRC_LIST += $(foreach src,$(tpm_src_command_ClockTimer_SRCS),tpm/src/command/ClockTimer/$(src))
