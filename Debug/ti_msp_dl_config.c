/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gTIMER_CarCTRL_AlternativeBackup;
DL_TimerG_backupConfig gTIMER_DingShiQiBackup;
DL_TimerA_backupConfig gTIMER_ShengGuangBackup;
DL_TimerA_backupConfig gTIMER_JiaJianSuBackup;
DL_SPI_backupConfig gSPI_0Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_MOTOR_init();
    SYSCFG_DL_TIMER_CarCTRL_init();
    SYSCFG_DL_TIMER_CarCTRL_Alternative_init();
    SYSCFG_DL_TIMER_DingShiQi_init();
    SYSCFG_DL_TIMER_ShengGuang_init();
    SYSCFG_DL_TIMER_JiaJianSu_init();
    SYSCFG_DL_I2C_MPU6050_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_0_init();
    /* Ensure backup structures have no valid state */

	gTIMER_CarCTRL_AlternativeBackup.backupRdy 	= false;
	gTIMER_DingShiQiBackup.backupRdy 	= false;
	gTIMER_ShengGuangBackup.backupRdy 	= false;
	gTIMER_JiaJianSuBackup.backupRdy 	= false;

	gSPI_0Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(TIMER_CarCTRL_Alternative_INST, &gTIMER_CarCTRL_AlternativeBackup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_DingShiQi_INST, &gTIMER_DingShiQiBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_ShengGuang_INST, &gTIMER_ShengGuangBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_JiaJianSu_INST, &gTIMER_JiaJianSuBackup);
	retStatus &= DL_SPI_saveConfiguration(SPI_0_INST, &gSPI_0Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(TIMER_CarCTRL_Alternative_INST, &gTIMER_CarCTRL_AlternativeBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_DingShiQi_INST, &gTIMER_DingShiQiBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_ShengGuang_INST, &gTIMER_ShengGuangBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_JiaJianSu_INST, &gTIMER_JiaJianSuBackup, false);
	retStatus &= DL_SPI_restoreConfiguration(SPI_0_INST, &gSPI_0Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_MOTOR_INST);
    DL_TimerG_reset(TIMER_CarCTRL_INST);
    DL_TimerG_reset(TIMER_CarCTRL_Alternative_INST);
    DL_TimerG_reset(TIMER_DingShiQi_INST);
    DL_TimerA_reset(TIMER_ShengGuang_INST);
    DL_TimerA_reset(TIMER_JiaJianSu_INST);
    DL_I2C_reset(I2C_MPU6050_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_MOTOR_INST);
    DL_TimerG_enablePower(TIMER_CarCTRL_INST);
    DL_TimerG_enablePower(TIMER_CarCTRL_Alternative_INST);
    DL_TimerG_enablePower(TIMER_DingShiQi_INST);
    DL_TimerA_enablePower(TIMER_ShengGuang_INST);
    DL_TimerA_enablePower(TIMER_JiaJianSu_INST);
    DL_I2C_enablePower(I2C_MPU6050_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR_C0_IOMUX,GPIO_PWM_MOTOR_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR_C0_PORT, GPIO_PWM_MOTOR_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR_C1_IOMUX,GPIO_PWM_MOTOR_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR_C1_PORT, GPIO_PWM_MOTOR_C1_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_MPU6050_IOMUX_SDA,
        GPIO_I2C_MPU6050_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_MPU6050_IOMUX_SCL,
        GPIO_I2C_MPU6050_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_MPU6050_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_MPU6050_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_SCLK, GPIO_SPI_0_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_PICO, GPIO_SPI_0_IOMUX_PICO_FUNC);

    DL_GPIO_initDigitalOutput(GPIO_BEEP_PIN_0_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_BUTTON2_PIN_S2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_LED1_PIN_LED1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MYLED_PIN_LED_IOMUX);

    DL_GPIO_initDigitalOutputFeatures(GPIO_LED_2_PIN_LED_GREEN_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_LED_2_PIN_LED_BLUE_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LED_2_PIN_LED_RED_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_CTRL_PIN_RST_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_CTRL_DC_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Encoder_PIN_Forward_Right_A_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Encoder_PIN_Forward_Right_B_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Encoder_PIN_Forward_Left_A_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Encoder_PIN_Forward_Left_B_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_PIN_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_PIN_AIN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_PIN_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_PIN_BIN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRAY_SERIAL_PIN_CLK_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_GRAY_SERIAL_PIN_FOWARD_DAT_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_COL_COL1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_COL_COL2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_COL_COL3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_COL_COL4_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_ROW_ROW1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_ROW_ROW2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_ROW_ROW3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_ROW_ROW4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_clearPins(GPIOA, GPIO_LED1_PIN_LED1_PIN |
		GPIO_GRAY_SERIAL_PIN_CLK_PIN);
    DL_GPIO_setPins(GPIOA, GPIO_COL_COL1_PIN |
		GPIO_COL_COL2_PIN |
		GPIO_COL_COL3_PIN |
		GPIO_COL_COL4_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_LED1_PIN_LED1_PIN |
		GPIO_GRAY_SERIAL_PIN_CLK_PIN |
		GPIO_COL_COL1_PIN |
		GPIO_COL_COL2_PIN |
		GPIO_COL_COL3_PIN |
		GPIO_COL_COL4_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_15_EDGE_RISE);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_28_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_Encoder_PIN_Forward_Right_A_PIN |
		GPIO_Encoder_PIN_Forward_Left_A_PIN);
    DL_GPIO_enableInterrupt(GPIOA, GPIO_Encoder_PIN_Forward_Right_A_PIN |
		GPIO_Encoder_PIN_Forward_Left_A_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_MYLED_PIN_LED_PIN |
		GPIO_LED_2_PIN_LED_GREEN_PIN |
		GPIO_LED_2_PIN_LED_BLUE_PIN |
		GPIO_LED_2_PIN_LED_RED_PIN |
		GPIO_CTRL_DC_PIN |
		GPIO_MOTOR_PIN_AIN1_PIN |
		GPIO_MOTOR_PIN_AIN2_PIN |
		GPIO_MOTOR_PIN_BIN1_PIN |
		GPIO_MOTOR_PIN_BIN2_PIN);
    DL_GPIO_setPins(GPIOB, GPIO_BEEP_PIN_0_PIN |
		GPIO_CTRL_PIN_RST_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_BEEP_PIN_0_PIN |
		GPIO_MYLED_PIN_LED_PIN |
		GPIO_LED_2_PIN_LED_GREEN_PIN |
		GPIO_LED_2_PIN_LED_BLUE_PIN |
		GPIO_LED_2_PIN_LED_RED_PIN |
		GPIO_CTRL_PIN_RST_PIN |
		GPIO_CTRL_DC_PIN |
		GPIO_MOTOR_PIN_AIN1_PIN |
		GPIO_MOTOR_PIN_AIN2_PIN |
		GPIO_MOTOR_PIN_BIN1_PIN |
		GPIO_MOTOR_PIN_BIN2_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();

}


/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_MOTORClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_MOTORConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 3200,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_MOTOR_init(void) {

    DL_TimerG_setClockConfig(
        PWM_MOTOR_INST, (DL_TimerG_ClockConfig *) &gPWM_MOTORClockConfig);

    DL_TimerG_initPWMMode(
        PWM_MOTOR_INST, (DL_TimerG_PWMConfig *) &gPWM_MOTORConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_MOTOR_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_MOTOR_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST, 3200, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(PWM_MOTOR_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_MOTOR_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST, 3200, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_MOTOR_INST);


    
    DL_TimerG_setCCPDirection(PWM_MOTOR_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 32000000 Hz / (1 * (31 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_CarCTRLClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 31U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_CarCTRL_INST_LOAD_VALUE = (10ms * 1000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_CarCTRLTimerConfig = {
    .period     = TIMER_CarCTRL_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_CarCTRL_init(void) {

    DL_TimerG_setClockConfig(TIMER_CarCTRL_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_CarCTRLClockConfig);

    DL_TimerG_initTimerMode(TIMER_CarCTRL_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_CarCTRLTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_CarCTRL_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_CarCTRL_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_CarCTRL_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 4000000 Hz / (8 * (31 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_CarCTRL_AlternativeClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 31U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_CarCTRL_Alternative_INST_LOAD_VALUE = (10 ms * 125000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_CarCTRL_AlternativeTimerConfig = {
    .period     = TIMER_CarCTRL_Alternative_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_CarCTRL_Alternative_init(void) {

    DL_TimerG_setClockConfig(TIMER_CarCTRL_Alternative_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_CarCTRL_AlternativeClockConfig);

    DL_TimerG_initTimerMode(TIMER_CarCTRL_Alternative_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_CarCTRL_AlternativeTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_CarCTRL_Alternative_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_CarCTRL_Alternative_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_CarCTRL_Alternative_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000 Hz = 4000000 Hz / (8 * (199 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_DingShiQiClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 199U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_DingShiQi_INST_LOAD_VALUE = (1.6s * 20000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_DingShiQiTimerConfig = {
    .period     = TIMER_DingShiQi_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_DingShiQi_init(void) {

    DL_TimerG_setClockConfig(TIMER_DingShiQi_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_DingShiQiClockConfig);

    DL_TimerG_initTimerMode(TIMER_DingShiQi_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_DingShiQiTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_DingShiQi_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_DingShiQi_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 4000000 Hz / (8 * (31 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_ShengGuangClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 31U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_ShengGuang_INST_LOAD_VALUE = (500 ms * 125000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_ShengGuangTimerConfig = {
    .period     = TIMER_ShengGuang_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_ShengGuang_init(void) {

    DL_TimerA_setClockConfig(TIMER_ShengGuang_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_ShengGuangClockConfig);

    DL_TimerA_initTimerMode(TIMER_ShengGuang_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_ShengGuangTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_ShengGuang_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_ShengGuang_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000 Hz = 4000000 Hz / (8 * (199 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_JiaJianSuClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 199U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_JiaJianSu_INST_LOAD_VALUE = (100 ms * 20000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_JiaJianSuTimerConfig = {
    .period     = TIMER_JiaJianSu_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_JiaJianSu_init(void) {

    DL_TimerA_setClockConfig(TIMER_JiaJianSu_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_JiaJianSuClockConfig);

    DL_TimerA_initTimerMode(TIMER_JiaJianSu_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_JiaJianSuTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_JiaJianSu_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_JiaJianSu_INST);





}


static const DL_I2C_ClockConfig gI2C_MPU6050ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_MPU6050_init(void) {

    DL_I2C_setClockConfig(I2C_MPU6050_INST,
        (DL_I2C_ClockConfig *) &gI2C_MPU6050ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_MPU6050_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_MPU6050_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_MPU6050_INST);
    /* Set frequency to 100000 Hz*/
    DL_I2C_setTimerPeriod(I2C_MPU6050_INST, 31);
    DL_I2C_setControllerTXFIFOThreshold(I2C_MPU6050_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_MPU6050_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_MPU6050_INST);

    /* Configure Interrupts */
    DL_I2C_enableInterrupt(I2C_MPU6050_INST,
                           DL_I2C_INTERRUPT_CONTROLLER_ARBITRATION_LOST |
                           DL_I2C_INTERRUPT_CONTROLLER_NACK |
                           DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_TRIGGER |
                           DL_I2C_INTERRUPT_CONTROLLER_RX_DONE |
                           DL_I2C_INTERRUPT_CONTROLLER_TX_DONE);


    /* Enable module */
    DL_I2C_enableController(I2C_MPU6050_INST);


}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_9600_BAUD, UART_0_FBRD_32_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_0_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI_0_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_0_init(void) {
    DL_SPI_setClockConfig(SPI_0_INST, (DL_SPI_ClockConfig *) &gSPI_0_clockConfig);

    DL_SPI_init(SPI_0_INST, (DL_SPI_Config *) &gSPI_0_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (32000000)/((1 + 1) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_0_INST, 1);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_0_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_0_INST);
}

