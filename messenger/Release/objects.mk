################################################################################
# Automatically-generated file. Do not edit!
################################################################################

USER_OBJS :=

ifeq "$(WINDOWS)" "YES"
LIBS := -llua52
else
LIBS := -llua52 -ldl
endif

