################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ioLibrary_Driver/Internet/httpServer/subdir.mk
-include ioLibrary_Driver/Internet/TFTP/subdir.mk
-include ioLibrary_Driver/Internet/SNTP/subdir.mk
-include ioLibrary_Driver/Internet/SNMP/subdir.mk
-include ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/subdir.mk
-include ioLibrary_Driver/Internet/MQTT/subdir.mk
-include ioLibrary_Driver/Internet/FTPServer/subdir.mk
-include ioLibrary_Driver/Internet/FTPClient/subdir.mk
-include ioLibrary_Driver/Internet/DNS/subdir.mk
-include ioLibrary_Driver/Internet/DHCP/subdir.mk
-include ioLibrary_Driver/Ethernet/W5500/subdir.mk
-include ioLibrary_Driver/Ethernet/W5300/subdir.mk
-include ioLibrary_Driver/Ethernet/W5200/subdir.mk
-include ioLibrary_Driver/Ethernet/W5100S/subdir.mk
-include ioLibrary_Driver/Ethernet/W5100/subdir.mk
-include ioLibrary_Driver/Ethernet/subdir.mk
-include ioLibrary_Driver/Application/multicast/subdir.mk
-include ioLibrary_Driver/Application/loopback/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
WIZ14xSR_Proj.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
WIZ14xSR_Proj.list \

OBJCOPY_BIN += \
WIZ14xSR_Proj.bin \


# All Target
all: WIZ14xSR_Proj.elf secondary-outputs

# Tool invocations
WIZ14xSR_Proj.elf: $(OBJS) $(USER_OBJS) /home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/STM32F103ZETX_FLASH.ld
	arm-none-eabi-gcc -o "WIZ14xSR_Proj.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/home/javakys/STM32CubeIDE/workspace_1.4.0/WIZ14xSR_Proj/STM32F103ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="WIZ14xSR_Proj.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

WIZ14xSR_Proj.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "WIZ14xSR_Proj.list"
	@echo 'Finished building: $@'
	@echo ' '

WIZ14xSR_Proj.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "WIZ14xSR_Proj.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
