################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
oled/oled.o: ../oled/oled.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/oled" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/PWM" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/KEY" -I"E:/desktop/大学/2024电赛/2024H/XLS-4-B/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/SPI_OLED/spi_oled/Servo" -gdwarf-3 -MMD -MP -MF"oled/$(basename $(<F)).d_raw" -MT"oled/$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


