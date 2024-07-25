################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DS1307.c \
../Src/Empty.c \
../Src/Pills.c \
../Src/User.c \
../Src/adc.c \
../Src/ble.c \
../Src/bluenrg_lps_hw_config.c \
../Src/bluenrg_lps_it.c \
../Src/huart.c \
../Src/project_main.c \
../Src/pwm.c \
../Src/spi.c \
../Src/util.c \
../Src/vl53l1x.c 

OBJS += \
./Src/DS1307.o \
./Src/Empty.o \
./Src/Pills.o \
./Src/User.o \
./Src/adc.o \
./Src/ble.o \
./Src/bluenrg_lps_hw_config.o \
./Src/bluenrg_lps_it.o \
./Src/huart.o \
./Src/project_main.o \
./Src/pwm.o \
./Src/spi.o \
./Src/util.o \
./Src/vl53l1x.o 

C_DEPS += \
./Src/DS1307.d \
./Src/Empty.d \
./Src/Pills.d \
./Src/User.d \
./Src/adc.d \
./Src/ble.d \
./Src/bluenrg_lps_hw_config.d \
./Src/bluenrg_lps_it.d \
./Src/huart.d \
./Src/project_main.d \
./Src/pwm.d \
./Src/spi.d \
./Src/util.d \
./Src/vl53l1x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -O0 -ffunction-sections -fdata-sections -g3 -std=c99 -DUSE_FULL_LL_DRIVER -DSTEVAL_IDB012V1 -DCONFIG_DEVICE_BLUENRG_LPS -DCONFIG_HW_SMPS_10uH -DCONFIG_HW_HSE_TUNE=32 -DCONFIG_HW_LS_RO -DUSER_BUTTON=BSP_PUSH1 -DBLE_STACK_BASIC_CONF -DCONFIG_DEVICE_BLUENRG_332 -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/CMSIS/Include" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/CMSIS/Device/ST/BlueNRG_LP/Include" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/Peripherals_Drivers/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Components/lps22hh_STdC/driver" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/BSP/Components/lsm6dsox_STdC/driver" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/Hal/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/AESMGR/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/OTA/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Profile_Central/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Profiles/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/Queued_Write/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLE_Application/layers_inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/Bluetooth_LE/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/NVMDB/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/BLECNTR/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/PKA/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/RNG/Inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES/Common" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES/CMAC" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/AES" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc/Common" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares/cryptolib/inc" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Inc/" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/VL53L1X_ULD_API/core" -I"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Drivers/VL53L1X_ULD_API/platform" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


