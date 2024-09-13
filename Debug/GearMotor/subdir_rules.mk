################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
GearMotor/%.o: ../GearMotor/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/desktop/XLS-2/oled" -I"E:/desktop/XLS-2" -I"E:/desktop/XLS-2/KEY" -I"E:/desktop/XLS-2/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/XLS-2/PWM" -gdwarf-3 -MMD -MP -MF"GearMotor/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


