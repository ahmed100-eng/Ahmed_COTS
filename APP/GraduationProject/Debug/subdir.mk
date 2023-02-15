################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prog.c \
../CLCD_program.c \
../DIO_program.c \
../EEPROM_prog.c \
../GIE_prog.c \
../PORT_prog.c \
../PWM_prog.c \
../TIMERS_prog.c \
../TWI_prog.c \
../USART_prog.c \
../main.c 

OBJS += \
./ADC_prog.o \
./CLCD_program.o \
./DIO_program.o \
./EEPROM_prog.o \
./GIE_prog.o \
./PORT_prog.o \
./PWM_prog.o \
./TIMERS_prog.o \
./TWI_prog.o \
./USART_prog.o \
./main.o 

C_DEPS += \
./ADC_prog.d \
./CLCD_program.d \
./DIO_program.d \
./EEPROM_prog.d \
./GIE_prog.d \
./PORT_prog.d \
./PWM_prog.d \
./TIMERS_prog.d \
./TWI_prog.d \
./USART_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


