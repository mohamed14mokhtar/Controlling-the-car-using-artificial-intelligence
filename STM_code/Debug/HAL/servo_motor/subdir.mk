################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/servo_motor/servo.c \
../HAL/servo_motor/servo_cfg.c 

OBJS += \
./HAL/servo_motor/servo.o \
./HAL/servo_motor/servo_cfg.o 

C_DEPS += \
./HAL/servo_motor/servo.d \
./HAL/servo_motor/servo_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/servo_motor/%.o HAL/servo_motor/%.su HAL/servo_motor/%.cyclo: ../HAL/servo_motor/%.c HAL/servo_motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I"F:/ARM_projects/car_control_with_ai/STM_code/HAL/Common" -I"F:/ARM_projects/car_control_with_ai/STM_code/HAL/servo_motor" -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-servo_motor

clean-HAL-2f-servo_motor:
	-$(RM) ./HAL/servo_motor/servo.cyclo ./HAL/servo_motor/servo.d ./HAL/servo_motor/servo.o ./HAL/servo_motor/servo.su ./HAL/servo_motor/servo_cfg.cyclo ./HAL/servo_motor/servo_cfg.d ./HAL/servo_motor/servo_cfg.o ./HAL/servo_motor/servo_cfg.su

.PHONY: clean-HAL-2f-servo_motor

