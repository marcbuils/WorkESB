################################################################################
# Automatically-generated file. Do not edit!
################################################################################

USER_OBJS :=

ifeq "$(WINDOWS)" "YES"
LIBS := -llua
else
LIBS := -llua -ldl
endif
