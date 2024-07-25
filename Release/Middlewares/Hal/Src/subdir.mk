################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Middlewares/Hal/Src/blue_unit_conversion.s \
../Middlewares/Hal/Src/context_switch.s \
../Middlewares/Hal/Src/osal_memcpy.s 

C_SRCS += \
../Middlewares/Hal/Src/clock.c \
../Middlewares/Hal/Src/fifo.c \
../Middlewares/Hal/Src/gp_timer.c \
../Middlewares/Hal/Src/hal_miscutil.c \
../Middlewares/Hal/Src/miscutil.c \
../Middlewares/Hal/Src/osal.c \
../Middlewares/Hal/Src/radio_ota.c 

OBJS += \
./Middlewares/Hal/Src/blue_unit_conversion.o \
./Middlewares/Hal/Src/clock.o \
./Middlewares/Hal/Src/context_switch.o \
./Middlewares/Hal/Src/fifo.o \
./Middlewares/Hal/Src/gp_timer.o \
./Middlewares/Hal/Src/hal_miscutil.o \
./Middlewares/Hal/Src/miscutil.o \
./Middlewares/Hal/Src/osal.o \
./Middlewares/Hal/Src/osal_memcpy.o \
./Middlewares/Hal/Src/radio_ota.o 

S_DEPS += \
./Middlewares/Hal/Src/blue_unit_conversion.d \
./Middlewares/Hal/Src/context_switch.d \
./Middlewares/Hal/Src/osal_memcpy.d 

C_DEPS += \
./Middlewares/Hal/Src/clock.d \
./Middlewares/Hal/Src/fifo.d \
./Middlewares/Hal/Src/gp_timer.d \
./Middlewares/Hal/Src/hal_miscutil.d \
./Middlewares/Hal/Src/miscutil.d \
./Middlewares/Hal/Src/osal.d \
./Middlewares/Hal/Src/radio_ota.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Hal/Src/%.o: ../Middlewares/Hal/Src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/Hal/Src/%.o: ../Middlewares/Hal/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -O0 -ffunction-sections -fdata-sections -g3 -std=c99 -DUSE_FULL_LL_DRIVER -DSTEVAL_IDB012V1 -DCONFIG_DEVICE_BLUENRG_LPS -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_LS_RO -DUSER_BUTTON=BSP_PUSH1 -DBLE_STACK_BASIC_CONF -DCONFIG_DEVICE_BLUENRG_332 -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/CMSIS/Include" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/CMSIS/Device/ST/BlueNRG_LP/Include" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/Peripherals_Drivers/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Components/lps22hh_STdC/driver" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Components/lsm6dsox_STdC/driver" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/Hal/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/AESMGR/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/OTA/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Profile_Central/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Profiles/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Queued_Write/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/layers_inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/Bluetooth_LE/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/NVMDB/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLECNTR/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/PKA/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/RNG/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES/Common" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES/CMAC" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/Common" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Inc/" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/VL53L1X_ULD_API/core" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/VL53L1X_ULD_API/platform" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


