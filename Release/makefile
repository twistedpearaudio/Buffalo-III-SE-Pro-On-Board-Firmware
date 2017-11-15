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
Buffalo-3-SE-Pro-OB.lss \

FLASH_IMAGE += \
Buffalo-3-SE-Pro-OB.hex \

EEPROM_IMAGE += \
Buffalo-3-SE-Pro-OB.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Buffalo-3-SE-Pro-OB.elf secondary-outputs

# Tool invocations
Buffalo-3-SE-Pro-OB.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Buffalo-3-SE-Pro-OB.map -mmcu=attiny85 -o "Buffalo-3-SE-Pro-OB.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Buffalo-3-SE-Pro-OB.lss: Buffalo-3-SE-Pro-OB.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Buffalo-3-SE-Pro-OB.elf  >"Buffalo-3-SE-Pro-OB.lss"
	@echo 'Finished building: $@'
	@echo ' '

Buffalo-3-SE-Pro-OB.hex: Buffalo-3-SE-Pro-OB.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Buffalo-3-SE-Pro-OB.elf  "Buffalo-3-SE-Pro-OB.hex"
	@echo 'Finished building: $@'
	@echo ' '

Buffalo-3-SE-Pro-OB.eep: Buffalo-3-SE-Pro-OB.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Buffalo-3-SE-Pro-OB.elf  "Buffalo-3-SE-Pro-OB.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Buffalo-3-SE-Pro-OB.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 Buffalo-3-SE-Pro-OB.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Buffalo-3-SE-Pro-OB.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
