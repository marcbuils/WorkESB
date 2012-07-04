################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../win32port/win32helpers/getopt.c \
../win32port/win32helpers/getopt_long.c \
../win32port/win32helpers/gettimeofday.c \
../win32port/win32helpers/websock-w32.c

OBJS += \
./win32port/win32helpers/getopt.o \
./win32port/win32helpers/getopt_long.o \
./win32port/win32helpers/gettimeofday.o \
./win32port/win32helpers/websock-w32.o

C_DEPS += \
./win32port/win32helpers/getopt.d \
./win32port/win32helpers/getopt_long.d \
./win32port/win32helpers/gettimeofday.d \
./win32port/win32helpers/websock-w32.d


# Each subdirectory must supply rules for building sources it contributes
win32port/win32helpers/%.o: ../win32port/win32helpers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


