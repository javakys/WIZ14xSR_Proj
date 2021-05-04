################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/DNS/dns.c 

OBJS += \
./ioLibrary_Driver/Internet/DNS/dns.o 

C_DEPS += \
./ioLibrary_Driver/Internet/DNS/dns.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/DNS/dns.o: ../ioLibrary_Driver/Internet/DNS/dns.c ioLibrary_Driver/Internet/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/jameskim/STM32CubeIDE/workspace_1.6.1/WIZ14xSR_Proj/ioLibrary_Driver/Ethernet" -I"/home/jameskim/STM32CubeIDE/workspace_1.6.1/WIZ14xSR_Proj/ioLibrary_Driver/Internet" -I"/home/jameskim/STM32CubeIDE/workspace_1.6.1/WIZ14xSR_Proj/ioLibrary_Driver/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/DNS/dns.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

