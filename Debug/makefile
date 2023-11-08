################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
Analog-Data-Logger-with-Interrupt-Driven-Alarm.lss \

FLASH_IMAGE += \
Analog-Data-Logger-with-Interrupt-Driven-Alarm.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf secondary-outputs

# Tool invocations
Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Analog-Data-Logger-with-Interrupt-Driven-Alarm.map -mmcu=atmega32 -o "Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Analog-Data-Logger-with-Interrupt-Driven-Alarm.lss: Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf  >"Analog-Data-Logger-with-Interrupt-Driven-Alarm.lss"
	@echo 'Finished building: $@'
	@echo ' '

Analog-Data-Logger-with-Interrupt-Driven-Alarm.hex: Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf  "Analog-Data-Logger-with-Interrupt-Driven-Alarm.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Analog-Data-Logger-with-Interrupt-Driven-Alarm.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
