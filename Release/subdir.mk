################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buffalo.c \
../I2C_CharDisplay.c \
../USI_I2C_Master.c 

OBJS += \
./Buffalo.o \
./I2C_CharDisplay.o \
./USI_I2C_Master.o 

C_DEPS += \
./Buffalo.d \
./I2C_CharDisplay.d \
./USI_I2C_Master.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny85 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


