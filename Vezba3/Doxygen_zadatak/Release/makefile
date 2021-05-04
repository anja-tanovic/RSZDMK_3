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
Doxygen_zadatak.lss \

FLASH_IMAGE += \
Doxygen_zadatak.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Doxygen_zadatak.elf secondary-outputs

# Tool invocations
Doxygen_zadatak.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Doxygen_zadatak.map -mmcu=atmega328p -o "Doxygen_zadatak.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Doxygen_zadatak.lss: Doxygen_zadatak.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Doxygen_zadatak.elf  >"Doxygen_zadatak.lss"
	@echo 'Finished building: $@'
	@echo ' '

Doxygen_zadatak.hex: Doxygen_zadatak.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Doxygen_zadatak.elf  "Doxygen_zadatak.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Doxygen_zadatak.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Doxygen_zadatak.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Doxygen_zadatak.elf
	@echo 'Invoking: AVRDude'
	C:\Users\VTS-zaposleni\Downloads\NE BRISATI\eclipse\bin\avrdude -pm328p -carduino -PCOM3 -Uflash:w:Doxygen_zadatak.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Doxygen_zadatak.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
