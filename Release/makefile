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
B3SEPro-OnBoard-Firmware.lss \

FLASH_IMAGE += \
B3SEPro-OnBoard-Firmware.hex \

EEPROM_IMAGE += \
B3SEPro-OnBoard-Firmware.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: B3SEPro-OnBoard-Firmware.elf secondary-outputs

# Tool invocations
B3SEPro-OnBoard-Firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,B3SEPro-OnBoard-Firmware.map -mmcu=attiny85 -o "B3SEPro-OnBoard-Firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

B3SEPro-OnBoard-Firmware.lss: B3SEPro-OnBoard-Firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S B3SEPro-OnBoard-Firmware.elf  >"B3SEPro-OnBoard-Firmware.lss"
	@echo 'Finished building: $@'
	@echo ' '

B3SEPro-OnBoard-Firmware.hex: B3SEPro-OnBoard-Firmware.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex B3SEPro-OnBoard-Firmware.elf  "B3SEPro-OnBoard-Firmware.hex"
	@echo 'Finished building: $@'
	@echo ' '

B3SEPro-OnBoard-Firmware.eep: B3SEPro-OnBoard-Firmware.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex B3SEPro-OnBoard-Firmware.elf  "B3SEPro-OnBoard-Firmware.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: B3SEPro-OnBoard-Firmware.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 B3SEPro-OnBoard-Firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) B3SEPro-OnBoard-Firmware.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
