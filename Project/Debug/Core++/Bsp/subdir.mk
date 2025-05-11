################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core++/Bsp/Bsp.cpp 

OBJS += \
./Core++/Bsp/Bsp.o 

CPP_DEPS += \
./Core++/Bsp/Bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Core++/Bsp/%.o Core++/Bsp/%.su Core++/Bsp/%.cyclo: ../Core++/Bsp/%.cpp Core++/Bsp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Core++/Inc -I../Core++/Bsp -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2b--2b--2f-Bsp

clean-Core-2b--2b--2f-Bsp:
	-$(RM) ./Core++/Bsp/Bsp.cyclo ./Core++/Bsp/Bsp.d ./Core++/Bsp/Bsp.o ./Core++/Bsp/Bsp.su

.PHONY: clean-Core-2b--2b--2f-Bsp

