################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/main.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/../src" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/.." -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/../../../src" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/include" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/../../../src/xf/port" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/../../common" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/Inc" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/rebor/Documents/HES/3eme/PTR/work/work/test-bench/test2/ide-sw4stm32-test2-idf/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


