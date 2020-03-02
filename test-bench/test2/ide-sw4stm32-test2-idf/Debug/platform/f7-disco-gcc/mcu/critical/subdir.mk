################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/Axel/Desktop/workRemy/src/platform/f7-disco-gcc/mcu/critical/critical.cpp 

OBJS += \
./platform/f7-disco-gcc/mcu/critical/critical.o 

CPP_DEPS += \
./platform/f7-disco-gcc/mcu/critical/critical.d 


# Each subdirectory must supply rules for building sources it contributes
platform/f7-disco-gcc/mcu/critical/critical.o: C:/Users/Axel/Desktop/workRemy/src/platform/f7-disco-gcc/mcu/critical/critical.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../src" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/.." -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf" -I"C:/Users/Axel/Desktop/workRemy/src/platform/f7-disco-gcc" -I"C:/Users/Axel/Desktop/workRemy/src/platform/f7-disco-gcc/mcu" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/include" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/port" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/port/default" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/port/default-idf" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/mdw" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/mdw/trace" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/../../common" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/Inc" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/Axel/Desktop/workRemy/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


