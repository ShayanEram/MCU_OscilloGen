################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core++/Src/AnalyzerExtern.cpp \
../Core++/Src/Bootloader.cpp \
../Core++/Src/DacExtern.cpp \
../Core++/Src/FuncAnalyser.cpp \
../Core++/Src/FuncGenerator.cpp \
../Core++/Src/Lcd.cpp \
../Core++/Src/MainCpp.cpp \
../Core++/Src/SerialConnection.cpp 

S_SRCS += \
../Core++/Src/asmFunc.s 

S_DEPS += \
./Core++/Src/asmFunc.d 

OBJS += \
./Core++/Src/AnalyzerExtern.o \
./Core++/Src/Bootloader.o \
./Core++/Src/DacExtern.o \
./Core++/Src/FuncAnalyser.o \
./Core++/Src/FuncGenerator.o \
./Core++/Src/Lcd.o \
./Core++/Src/MainCpp.o \
./Core++/Src/SerialConnection.o \
./Core++/Src/asmFunc.o 

CPP_DEPS += \
./Core++/Src/AnalyzerExtern.d \
./Core++/Src/Bootloader.d \
./Core++/Src/DacExtern.d \
./Core++/Src/FuncAnalyser.d \
./Core++/Src/FuncGenerator.d \
./Core++/Src/Lcd.d \
./Core++/Src/MainCpp.d \
./Core++/Src/SerialConnection.d 


# Each subdirectory must supply rules for building sources it contributes
Core++/Src/%.o Core++/Src/%.su Core++/Src/%.cyclo: ../Core++/Src/%.cpp Core++/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Core++/Inc -I../Core++/Bsp -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core++/Src/%.o: ../Core++/Src/%.s Core++/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2b--2b--2f-Src

clean-Core-2b--2b--2f-Src:
	-$(RM) ./Core++/Src/AnalyzerExtern.cyclo ./Core++/Src/AnalyzerExtern.d ./Core++/Src/AnalyzerExtern.o ./Core++/Src/AnalyzerExtern.su ./Core++/Src/Bootloader.cyclo ./Core++/Src/Bootloader.d ./Core++/Src/Bootloader.o ./Core++/Src/Bootloader.su ./Core++/Src/DacExtern.cyclo ./Core++/Src/DacExtern.d ./Core++/Src/DacExtern.o ./Core++/Src/DacExtern.su ./Core++/Src/FuncAnalyser.cyclo ./Core++/Src/FuncAnalyser.d ./Core++/Src/FuncAnalyser.o ./Core++/Src/FuncAnalyser.su ./Core++/Src/FuncGenerator.cyclo ./Core++/Src/FuncGenerator.d ./Core++/Src/FuncGenerator.o ./Core++/Src/FuncGenerator.su ./Core++/Src/Lcd.cyclo ./Core++/Src/Lcd.d ./Core++/Src/Lcd.o ./Core++/Src/Lcd.su ./Core++/Src/MainCpp.cyclo ./Core++/Src/MainCpp.d ./Core++/Src/MainCpp.o ./Core++/Src/MainCpp.su ./Core++/Src/SerialConnection.cyclo ./Core++/Src/SerialConnection.d ./Core++/Src/SerialConnection.o ./Core++/Src/SerialConnection.su ./Core++/Src/asmFunc.d ./Core++/Src/asmFunc.o

.PHONY: clean-Core-2b--2b--2f-Src

