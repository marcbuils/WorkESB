################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../messenger_gateway_websockets/src/Log.cpp \
../messenger_gateway_websockets/src/messenger_gateway.cpp 

OBJS += \
./messenger_gateway_websockets/src/Log.o \
./messenger_gateway_websockets/src/messenger_gateway.o 

CPP_DEPS += \
./messenger_gateway_websockets/src/Log.d \
./messenger_gateway_websockets/src/messenger_gateway.d 


# Each subdirectory must supply rules for building sources it contributes
messenger_gateway_websockets/src/%.o: ../messenger_gateway_websockets/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../messenger_gateway_websockets/include" -I"${CSIEMESSENGER_ROOT}/include" -I"${JSONCPP_ROOT}/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


