################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Ultrasonic/%.o: ../Ultrasonic/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/desktop/XLS-3-Bcar/oled" -I"E:/desktop/XLS-3-Bcar" -I"E:/desktop/XLS-3-Bcar/Ultrasonic" -I"E:/desktop/XLS-3-Bcar/Motor" -I"E:/desktop/XLS-3-Bcar/KEY" -I"E:/desktop/XLS-3-Bcar/GRAY SENSOR" -I"E:/desktop/XLS-3-Bcar/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/XLS-3-Bcar/PWM" -gdwarf-3 -MMD -MP -MF"Ultrasonic/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


