################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../WESBMessenger.cpp \
../Log.cpp 

OBJS += \
./WESBMessenger.o \
./Log.o 

CPP_DEPS += \
./WESBMessenger.d \
./Log.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/marc/tools/boost/boost_1_49_0" -I"${JSONCPP_ROOT}/include" -I"${SIMD_INSTALL_DIR}/include" -I"${OSPL_HOME}/include/dcps/C++/SACPP" -I"${OSPL_HOME}/include/sys" -I"${OSPL_HOME}/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


