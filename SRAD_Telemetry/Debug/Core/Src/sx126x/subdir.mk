################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sx126x/lr_fhss_mac.c \
../Core/Src/sx126x/sx126x.c \
../Core/Src/sx126x/sx126x_driver_version.c \
../Core/Src/sx126x/sx126x_hal.c \
../Core/Src/sx126x/sx126x_lr_fhss.c 

OBJS += \
./Core/Src/sx126x/lr_fhss_mac.o \
./Core/Src/sx126x/sx126x.o \
./Core/Src/sx126x/sx126x_driver_version.o \
./Core/Src/sx126x/sx126x_hal.o \
./Core/Src/sx126x/sx126x_lr_fhss.o 

C_DEPS += \
./Core/Src/sx126x/lr_fhss_mac.d \
./Core/Src/sx126x/sx126x.d \
./Core/Src/sx126x/sx126x_driver_version.d \
./Core/Src/sx126x/sx126x_hal.d \
./Core/Src/sx126x/sx126x_lr_fhss.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sx126x/%.o Core/Src/sx126x/%.su Core/Src/sx126x/%.cyclo: ../Core/Src/sx126x/%.c Core/Src/sx126x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sx126x

clean-Core-2f-Src-2f-sx126x:
	-$(RM) ./Core/Src/sx126x/lr_fhss_mac.cyclo ./Core/Src/sx126x/lr_fhss_mac.d ./Core/Src/sx126x/lr_fhss_mac.o ./Core/Src/sx126x/lr_fhss_mac.su ./Core/Src/sx126x/sx126x.cyclo ./Core/Src/sx126x/sx126x.d ./Core/Src/sx126x/sx126x.o ./Core/Src/sx126x/sx126x.su ./Core/Src/sx126x/sx126x_driver_version.cyclo ./Core/Src/sx126x/sx126x_driver_version.d ./Core/Src/sx126x/sx126x_driver_version.o ./Core/Src/sx126x/sx126x_driver_version.su ./Core/Src/sx126x/sx126x_hal.cyclo ./Core/Src/sx126x/sx126x_hal.d ./Core/Src/sx126x/sx126x_hal.o ./Core/Src/sx126x/sx126x_hal.su ./Core/Src/sx126x/sx126x_lr_fhss.cyclo ./Core/Src/sx126x/sx126x_lr_fhss.d ./Core/Src/sx126x/sx126x_lr_fhss.o ./Core/Src/sx126x/sx126x_lr_fhss.su

.PHONY: clean-Core-2f-Src-2f-sx126x

