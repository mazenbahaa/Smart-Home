################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MTIMER0/MTIMER0_prg.c 

OBJS += \
./MCAL/MTIMER0/MTIMER0_prg.o 

C_DEPS += \
./MCAL/MTIMER0/MTIMER0_prg.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MTIMER0/%.o: ../MCAL/MTIMER0/%.c MCAL/MTIMER0/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\LIB" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MADC" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MDIO" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MEXTI" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MGIE" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MIIC" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MTIMER0" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MTIMER1" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\MCAL\MWDTIMER" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\HAL\HEEPROM" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\HAL\HKPAD" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\HAL\HLCD" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\HAL\HLED" -I"C:\Users\Elkhashab\Desktop\AVR-WorkSpace\SmartHome\HAL\HTEMPERATURE" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


