################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core++/Bsp/Src/BspPic.cpp \
../Core++/Bsp/Src/BspStm.cpp 

OBJS += \
./Core++/Bsp/Src/BspPic.o \
./Core++/Bsp/Src/BspStm.o 

CPP_DEPS += \
./Core++/Bsp/Src/BspPic.d \
./Core++/Bsp/Src/BspStm.d 


# Each subdirectory must supply rules for building sources it contributes
Core++/Bsp/Src/%.o Core++/Bsp/Src/%.su Core++/Bsp/Src/%.cyclo: ../Core++/Bsp/Src/%.cpp Core++/Bsp/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Core++/Inc -I../Core++/Bsp/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2b--2b--2f-Bsp-2f-Src

clean-Core-2b--2b--2f-Bsp-2f-Src:
	-$(RM) ./Core++/Bsp/Src/BspPic.cyclo ./Core++/Bsp/Src/BspPic.d ./Core++/Bsp/Src/BspPic.o ./Core++/Bsp/Src/BspPic.su ./Core++/Bsp/Src/BspStm.cyclo ./Core++/Bsp/Src/BspStm.d ./Core++/Bsp/Src/BspStm.o ./Core++/Bsp/Src/BspStm.su

.PHONY: clean-Core-2b--2b--2f-Bsp-2f-Src

