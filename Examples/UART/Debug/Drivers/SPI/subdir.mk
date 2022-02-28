################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/lucifer/github/STM32F1/Drivers/SPI/spi_driver.c 

OBJS += \
./Drivers/SPI/spi_driver.o 

C_DEPS += \
./Drivers/SPI/spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SPI/spi_driver.o: /home/lucifer/github/STM32F1/Drivers/SPI/spi_driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RBTx -DNUCLEO_F103RB -DDEBUG -DSTM32F10X_MD -I"/home/lucifer/github/STM32F1/Drivers/SPI" -I"/home/lucifer/github/STM32F1/Examples/UART/inc" -I"/home/lucifer/github/STM32F1/Drivers/uart" -I"/home/lucifer/github/STM32F1/Drivers" -I"/home/lucifer/github/STM32F1/Examples/UART/CMSIS/device" -I"/home/lucifer/github/STM32F1/Examples/UART/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


