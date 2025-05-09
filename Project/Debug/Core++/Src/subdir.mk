################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core++/Src/DacExtern.cpp \
../Core++/Src/MainCpp.cpp \
../Core++/Src/Signal.cpp 

OBJS += \
./Core++/Src/DacExtern.o \
./Core++/Src/MainCpp.o \
./Core++/Src/Signal.o 

CPP_DEPS += \
./Core++/Src/DacExtern.d \
./Core++/Src/MainCpp.d \
./Core++/Src/Signal.d 


# Each subdirectory must supply rules for building sources it contributes
Core++/Src/%.o Core++/Src/%.su Core++/Src/%.cyclo: ../Core++/Src/%.cpp Core++/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Core++/Inc -I../Core++/Bsp/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2b--2b--2f-Src

clean-Core-2b--2b--2f-Src:
	-$(RM) ./Core++/Src/DacExtern.cyclo ./Core++/Src/DacExtern.d ./Core++/Src/DacExtern.o ./Core++/Src/DacExtern.su ./Core++/Src/MainCpp.cyclo ./Core++/Src/MainCpp.d ./Core++/Src/MainCpp.o ./Core++/Src/MainCpp.su ./Core++/Src/Signal.cyclo ./Core++/Src/Signal.d ./Core++/Src/Signal.o ./Core++/Src/Signal.su

.PHONY: clean-Core-2b--2b--2f-Src

