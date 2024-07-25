################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include Middlewares/cryptolib/subdir.mk
-include Middlewares/RNG/Src/subdir.mk
-include Middlewares/PKA/Src/subdir.mk
-include Middlewares/NVMDB/Src/subdir.mk
-include Middlewares/Hal/Src/subdir.mk
-include Middlewares/Bluetooth_LE/src/subdir.mk
-include Middlewares/BLE_Application/Profiles/Src/subdir.mk
-include Middlewares/BLECNTR/Src/subdir.mk
-include Middlewares/AESMGR/Src/subdir.mk
-include Drivers/VL53L1X_ULD_API/platform/subdir.mk
-include Drivers/VL53L1X_ULD_API/core/subdir.mk
-include Drivers/Peripherals_Drivers/Src/subdir.mk
-include Drivers/BSP/Src/subdir.mk
-include Drivers/BSP/Components/lsm6dsox_STdC/driver/subdir.mk
-include Drivers/BSP/Components/lps22hh_STdC/driver/subdir.mk
-include CMSIS/Device/ST/BlueNRG_LP/Source/subdir.mk
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
POST_BUILD_OBJCOPY += \
EmptyMapper_proj_Release.hex \

POST_BUILD_PRINT_SIZE += \
elf-size \


# All Target
all: EmptyMapper_proj_Release.elf secondary-outputs

# Tool invocations
EmptyMapper_proj_Release.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -nostartfiles -nodefaultlibs -Wl,--gc-sections -Wl,-Map="EmptyMapper_proj_Release.map" -T"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/BlueNRG_LPS.ld" -L"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares\BLE_Stack" -L"C:/Users/rossi/OneDrive - Politecnico di Bari/Desktop/Progetto Iot/EmptyMapper_proj/EmptyMapper_proj/WiSE-Studio/Middlewares\cryptolib" -Wl,--cref,--defsym=CONFIG_DEVICE_BLUENRG_332=1 --specs=nano.specs -u _printf_float -o "EmptyMapper_proj_Release.elf"  -Wl,--start-group @"objects.list" $(USER_OBJS) $(LIBS) -lm -lc  -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

EmptyMapper_proj_Release.hex: EmptyMapper_proj_Release.elf
	@echo 'Invoking: Generate binary'
	arm-none-eabi-objcopy -O ihex "EmptyMapper_proj_Release.elf"  "EmptyMapper_proj_Release.hex"
	@echo 'Finished building: $@'
	@echo ' '

elf-size: EmptyMapper_proj_Release.elf
	@echo 'Invoking: Print Size'
	arm-none-eabi-size -B "EmptyMapper_proj_Release.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(POST_BUILD_OBJCOPY)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(POST_BUILD_PRINT_SIZE)$(C_DEPS) EmptyMapper_proj_Release.elf EmptyMapper_proj_Release.bin *.map
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O binary EmptyMapper_proj_Release.elf EmptyMapper_proj_Release.bin
	-@echo ' '

secondary-outputs: $(POST_BUILD_OBJCOPY) $(POST_BUILD_PRINT_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
