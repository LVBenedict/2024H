################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Servo/%.o: ../Servo/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccstheia140/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/desktop/SPI_OLED/spi_oled/oled" -I"E:/desktop/SPI_OLED/spi_oled" -I"E:/desktop/SPI_OLED/spi_oled/KEY" -I"E:/desktop/SPI_OLED/spi_oled/Debug" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs1271/mspm0_sdk_2_01_00_03/source" -I"E:/desktop/SPI_OLED/spi_oled/Servo" -gdwarf-3 -MMD -MP -MF"Servo/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


