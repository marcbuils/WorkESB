################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../win32port/zlib/compress.c \
../win32port/zlib/adler32.c \
../win32port/zlib/crc32.c \
../win32port/zlib/deflate.c \
../win32port/zlib/gzclose.c \
../win32port/zlib/gzio.c \
../win32port/zlib/gzlib.c \
../win32port/zlib/gzread.c \
../win32port/zlib/gzwrite.c \
../win32port/zlib/infback.c \
../win32port/zlib/inffast.c \
../win32port/zlib/inflate.c \
../win32port/zlib/inftrees.c \
../win32port/zlib/trees.c \
../win32port/zlib/uncompr.c \
../win32port/zlib/zutil.c

OBJS += \
./win32port/zlib/compress.o \
./win32port/zlib/adler32.o \
./win32port/zlib/crc32.o \
./win32port/zlib/deflate.o \
./win32port/zlib/gzclose.o \
./win32port/zlib/gzio.o \
./win32port/zlib/gzlib.o \
./win32port/zlib/gzread.o \
./win32port/zlib/gzwrite.o \
./win32port/zlib/infback.o \
./win32port/zlib/inffast.o \
./win32port/zlib/inflate.o \
./win32port/zlib/inftrees.o \
./win32port/zlib/trees.o \
./win32port/zlib/uncompr.o \
./win32port/zlib/zutil.o

C_DEPS += \
./win32port/zlib/compress.d \
./win32port/zlib/adler32.d \
./win32port/zlib/crc32.d \
./win32port/zlib/deflate.d \
./win32port/zlib/gzclose.d \
./win32port/zlib/gzio.d \
./win32port/zlib/gzlib.d \
./win32port/zlib/gzread.d \
./win32port/zlib/gzwrite.d \
./win32port/zlib/infback.d \
./win32port/zlib/inffast.d \
./win32port/zlib/inflate.d \
./win32port/zlib/inftrees.d \
./win32port/zlib/trees.d \
./win32port/zlib/uncompr.d \
./win32port/zlib/zutil.d


# Each subdirectory must supply rules for building sources it contributes
win32port/zlib/%.o: ../win32port/zlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


