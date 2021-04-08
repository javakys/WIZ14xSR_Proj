################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/TFTP/netutil.c \
../ioLibrary_Driver/Internet/TFTP/tftp.c 

OBJS += \
./ioLibrary_Driver/Internet/TFTP/netutil.o \
./ioLibrary_Driver/Internet/TFTP/tftp.o 

C_DEPS += \
./ioLibrary_Driver/Internet/TFTP/netutil.d \
./ioLibrary_Driver/Internet/TFTP/tftp.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/TFTP/netutil.o: ../ioLibrary_Driver/Internet/TFTP/netutil.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Ethernet -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Internet -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Application -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/TFTP/netutil.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ioLibrary_Driver/Internet/TFTP/tftp.o: ../ioLibrary_Driver/Internet/TFTP/tftp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Ethernet -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Internet -I/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/ioLibrary_Driver/Application -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ioLibrary_Driver/Internet/TFTP/tftp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

