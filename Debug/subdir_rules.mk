################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
XLS-4-B.o: ../XLS-4-B.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/oled" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/MPU6050" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Ultrasonic" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Motor" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/GRAY SENSOR" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/PWM" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/KEY" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c: ../XLS-4-B.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ti/ccstheia140/ccs/utils/sysconfig_1.20.0/sysconfig_cli.bat" --script "E:/desktop/大学/2024电赛/2024H/XLS-4-B/XLS-4-B.syscfg" -o "." -s "D:/ti/ccs1271/mspm0_sdk_2_01_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/oled" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/MPU6050" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Ultrasonic" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Motor" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/KEY" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/GRAY SENSOR" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/PWM" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


