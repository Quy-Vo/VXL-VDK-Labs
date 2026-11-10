################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Copy\ of\ Src/button.c \
../Core/Copy\ of\ Src/fsm_automatic.c \
../Core/Copy\ of\ Src/fsm_manual.c \
../Core/Copy\ of\ Src/global.c \
../Core/Copy\ of\ Src/led.c \
../Core/Copy\ of\ Src/main.c \
../Core/Copy\ of\ Src/software_timer.c \
../Core/Copy\ of\ Src/stm32f1xx_hal_msp.c \
../Core/Copy\ of\ Src/stm32f1xx_it.c \
../Core/Copy\ of\ Src/syscalls.c \
../Core/Copy\ of\ Src/sysmem.c \
../Core/Copy\ of\ Src/system_stm32f1xx.c 

OBJS += \
./Core/Copy\ of\ Src/button.o \
./Core/Copy\ of\ Src/fsm_automatic.o \
./Core/Copy\ of\ Src/fsm_manual.o \
./Core/Copy\ of\ Src/global.o \
./Core/Copy\ of\ Src/led.o \
./Core/Copy\ of\ Src/main.o \
./Core/Copy\ of\ Src/software_timer.o \
./Core/Copy\ of\ Src/stm32f1xx_hal_msp.o \
./Core/Copy\ of\ Src/stm32f1xx_it.o \
./Core/Copy\ of\ Src/syscalls.o \
./Core/Copy\ of\ Src/sysmem.o \
./Core/Copy\ of\ Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Copy\ of\ Src/button.d \
./Core/Copy\ of\ Src/fsm_automatic.d \
./Core/Copy\ of\ Src/fsm_manual.d \
./Core/Copy\ of\ Src/global.d \
./Core/Copy\ of\ Src/led.d \
./Core/Copy\ of\ Src/main.d \
./Core/Copy\ of\ Src/software_timer.d \
./Core/Copy\ of\ Src/stm32f1xx_hal_msp.d \
./Core/Copy\ of\ Src/stm32f1xx_it.d \
./Core/Copy\ of\ Src/syscalls.d \
./Core/Copy\ of\ Src/sysmem.d \
./Core/Copy\ of\ Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Copy\ of\ Src/button.o: ../Core/Copy\ of\ Src/button.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/button.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/fsm_automatic.o: ../Core/Copy\ of\ Src/fsm_automatic.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/fsm_automatic.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/fsm_manual.o: ../Core/Copy\ of\ Src/fsm_manual.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/fsm_manual.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/global.o: ../Core/Copy\ of\ Src/global.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/global.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/led.o: ../Core/Copy\ of\ Src/led.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/main.o: ../Core/Copy\ of\ Src/main.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/software_timer.o: ../Core/Copy\ of\ Src/software_timer.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/software_timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/stm32f1xx_hal_msp.o: ../Core/Copy\ of\ Src/stm32f1xx_hal_msp.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/stm32f1xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/stm32f1xx_it.o: ../Core/Copy\ of\ Src/stm32f1xx_it.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/stm32f1xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/syscalls.o: ../Core/Copy\ of\ Src/syscalls.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/sysmem.o: ../Core/Copy\ of\ Src/sysmem.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Copy\ of\ Src/system_stm32f1xx.o: ../Core/Copy\ of\ Src/system_stm32f1xx.c Core/Copy\ of\ Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Copy of Src/system_stm32f1xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

