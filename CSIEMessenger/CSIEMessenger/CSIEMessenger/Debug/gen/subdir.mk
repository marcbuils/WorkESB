################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gen/Shared_Data.cpp \
../gen/Shared_DataDcps.cpp \
../gen/Shared_DataDcps_impl.cpp \
../gen/Shared_DataSplDcps.cpp 

OBJS += \
./gen/Shared_Data.o \
./gen/Shared_DataDcps.o \
./gen/Shared_DataDcps_impl.o \
./gen/Shared_DataSplDcps.o 

CPP_DEPS += \
./gen/Shared_Data.d \
./gen/Shared_DataDcps.d \
./gen/Shared_DataDcps_impl.d \
./gen/Shared_DataSplDcps.d 


# Each subdirectory must supply rules for building sources it contributes
gen/%.o: ../gen/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"${JSONCPP_ROOT}/include" -I"${SIMD_INSTALL_DIR}/include" -I"${OSPL_HOME}/include/dcps/C++/SACPP" -I"${OSPL_HOME}/include/sys" -I"${OSPL_HOME}/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


