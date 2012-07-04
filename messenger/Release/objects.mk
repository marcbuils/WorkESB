################################################################################
# Automatically-generated file. Do not edit!
################################################################################

USER_OBJS :=

ifeq "$(WINDOWS)" "YES"
LIBS := -llua5.1
else
LIBS := -llua5.1 -ldl
endif

