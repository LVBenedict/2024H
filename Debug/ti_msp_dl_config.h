/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_MOTOR */
#define PWM_MOTOR_INST                                                     TIMG0
#define PWM_MOTOR_INST_IRQHandler                               TIMG0_IRQHandler
#define PWM_MOTOR_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define PWM_MOTOR_INST_CLK_FREQ                                         32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_MOTOR_C0_PORT                                             GPIOA
#define GPIO_PWM_MOTOR_C0_PIN                                     DL_GPIO_PIN_12
#define GPIO_PWM_MOTOR_C0_IOMUX                                  (IOMUX_PINCM34)
#define GPIO_PWM_MOTOR_C0_IOMUX_FUNC                 IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_MOTOR_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTOR_C1_PORT                                             GPIOA
#define GPIO_PWM_MOTOR_C1_PIN                                     DL_GPIO_PIN_13
#define GPIO_PWM_MOTOR_C1_IOMUX                                  (IOMUX_PINCM35)
#define GPIO_PWM_MOTOR_C1_IOMUX_FUNC                 IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_MOTOR_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for TIMER_CarCTRL */
#define TIMER_CarCTRL_INST                                               (TIMG8)
#define TIMER_CarCTRL_INST_IRQHandler                           TIMG8_IRQHandler
#define TIMER_CarCTRL_INST_INT_IRQN                             (TIMG8_INT_IRQn)
#define TIMER_CarCTRL_INST_LOAD_VALUE                                    (9999U)
/* Defines for TIMER_CarCTRL_Alternative */
#define TIMER_CarCTRL_Alternative_INST                                   (TIMG7)
#define TIMER_CarCTRL_Alternative_INST_IRQHandler                        TIMG7_IRQHandler
#define TIMER_CarCTRL_Alternative_INST_INT_IRQN                        (TIMG7_INT_IRQn)
#define TIMER_CarCTRL_Alternative_INST_LOAD_VALUE                                 (1249U)
/* Defines for TIMER_DingShiQi */
#define TIMER_DingShiQi_INST                                             (TIMG6)
#define TIMER_DingShiQi_INST_IRQHandler                         TIMG6_IRQHandler
#define TIMER_DingShiQi_INST_INT_IRQN                           (TIMG6_INT_IRQn)
#define TIMER_DingShiQi_INST_LOAD_VALUE                                 (31999U)
/* Defines for TIMER_ShengGuang */
#define TIMER_ShengGuang_INST                                            (TIMA0)
#define TIMER_ShengGuang_INST_IRQHandler                        TIMA0_IRQHandler
#define TIMER_ShengGuang_INST_INT_IRQN                          (TIMA0_INT_IRQn)
#define TIMER_ShengGuang_INST_LOAD_VALUE                                (62499U)
/* Defines for TIMER_JiaJianSu */
#define TIMER_JiaJianSu_INST                                             (TIMA1)
#define TIMER_JiaJianSu_INST_IRQHandler                         TIMA1_IRQHandler
#define TIMER_JiaJianSu_INST_INT_IRQN                           (TIMA1_INT_IRQn)
#define TIMER_JiaJianSu_INST_LOAD_VALUE                                  (1999U)




/* Defines for I2C_MPU6050 */
#define I2C_MPU6050_INST                                                    I2C1
#define I2C_MPU6050_INST_IRQHandler                              I2C1_IRQHandler
#define I2C_MPU6050_INST_INT_IRQN                                  I2C1_INT_IRQn
#define I2C_MPU6050_BUS_SPEED_HZ                                          100000
#define GPIO_I2C_MPU6050_SDA_PORT                                          GPIOB
#define GPIO_I2C_MPU6050_SDA_PIN                                   DL_GPIO_PIN_3
#define GPIO_I2C_MPU6050_IOMUX_SDA                               (IOMUX_PINCM16)
#define GPIO_I2C_MPU6050_IOMUX_SDA_FUNC                IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_MPU6050_SCL_PORT                                          GPIOB
#define GPIO_I2C_MPU6050_SCL_PIN                                   DL_GPIO_PIN_2
#define GPIO_I2C_MPU6050_IOMUX_SCL                               (IOMUX_PINCM15)
#define GPIO_I2C_MPU6050_IOMUX_SCL_FUNC                IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                       DL_GPIO_PIN_8
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM25)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM25_PF_SPI1_PICO
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOB
#define GPIO_SPI_0_SCLK_PIN                                       DL_GPIO_PIN_9
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM26)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM26_PF_SPI1_SCLK
#define GPIO_SPI_0_CD_PORT                                                GPIOB
#define GPIO_SPI_0_CD_PIN                                         DL_GPIO_PIN_1
#define GPIO_SPI_0_IOMUX_CD                                     (IOMUX_PINCM13)
#define GPIO_SPI_0_IOMUX_CD_FUNC             IOMUX_PINCM13_PF_SPI1_CS3_CD_POCI3



/* Port definition for Pin Group GPIO_BEEP */
#define GPIO_BEEP_PORT                                                   (GPIOB)

/* Defines for PIN_0: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_BEEP_PIN_0_PIN                                     (DL_GPIO_PIN_19)
#define GPIO_BEEP_PIN_0_IOMUX                                    (IOMUX_PINCM45)
/* Port definition for Pin Group GPIO_BUTTON2 */
#define GPIO_BUTTON2_PORT                                                (GPIOB)

/* Defines for PIN_S2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_BUTTON2_PIN_S2_PIN                                 (DL_GPIO_PIN_21)
#define GPIO_BUTTON2_PIN_S2_IOMUX                                (IOMUX_PINCM49)
/* Port definition for Pin Group GPIO_LED1 */
#define GPIO_LED1_PORT                                                   (GPIOA)

/* Defines for PIN_LED1: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_LED1_PIN_LED1_PIN                                   (DL_GPIO_PIN_0)
#define GPIO_LED1_PIN_LED1_IOMUX                                  (IOMUX_PINCM1)
/* Port definition for Pin Group GPIO_MYLED */
#define GPIO_MYLED_PORT                                                  (GPIOB)

/* Defines for PIN_LED: GPIOB.4 with pinCMx 17 on package pin 52 */
#define GPIO_MYLED_PIN_LED_PIN                                   (DL_GPIO_PIN_4)
#define GPIO_MYLED_PIN_LED_IOMUX                                 (IOMUX_PINCM17)
/* Port definition for Pin Group GPIO_LED_2 */
#define GPIO_LED_2_PORT                                                  (GPIOB)

/* Defines for PIN_LED_GREEN: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_LED_2_PIN_LED_GREEN_PIN                            (DL_GPIO_PIN_27)
#define GPIO_LED_2_PIN_LED_GREEN_IOMUX                           (IOMUX_PINCM58)
/* Defines for PIN_LED_BLUE: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_LED_2_PIN_LED_BLUE_PIN                             (DL_GPIO_PIN_22)
#define GPIO_LED_2_PIN_LED_BLUE_IOMUX                            (IOMUX_PINCM50)
/* Defines for PIN_LED_RED: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_LED_2_PIN_LED_RED_PIN                              (DL_GPIO_PIN_26)
#define GPIO_LED_2_PIN_LED_RED_IOMUX                             (IOMUX_PINCM57)
/* Port definition for Pin Group GPIO_CTRL */
#define GPIO_CTRL_PORT                                                   (GPIOB)

/* Defines for PIN_RST: GPIOB.7 with pinCMx 24 on package pin 59 */
#define GPIO_CTRL_PIN_RST_PIN                                    (DL_GPIO_PIN_7)
#define GPIO_CTRL_PIN_RST_IOMUX                                  (IOMUX_PINCM24)
/* Defines for DC: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_CTRL_DC_PIN                                         (DL_GPIO_PIN_6)
#define GPIO_CTRL_DC_IOMUX                                       (IOMUX_PINCM23)
/* Port definition for Pin Group GPIO_Encoder */
#define GPIO_Encoder_PORT                                                (GPIOA)

/* Defines for PIN_Forward_Right_A: GPIOA.15 with pinCMx 37 on package pin 8 */
// pins affected by this interrupt request:["PIN_Forward_Right_A","PIN_Forward_Left_A"]
#define GPIO_Encoder_INT_IRQN                                   (GPIOA_INT_IRQn)
#define GPIO_Encoder_INT_IIDX                   (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_Encoder_PIN_Forward_Right_A_IIDX               (DL_GPIO_IIDX_DIO15)
#define GPIO_Encoder_PIN_Forward_Right_A_PIN                    (DL_GPIO_PIN_15)
#define GPIO_Encoder_PIN_Forward_Right_A_IOMUX                   (IOMUX_PINCM37)
/* Defines for PIN_Forward_Right_B: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_Encoder_PIN_Forward_Right_B_PIN                    (DL_GPIO_PIN_22)
#define GPIO_Encoder_PIN_Forward_Right_B_IOMUX                   (IOMUX_PINCM47)
/* Defines for PIN_Forward_Left_A: GPIOA.28 with pinCMx 3 on package pin 35 */
#define GPIO_Encoder_PIN_Forward_Left_A_IIDX                (DL_GPIO_IIDX_DIO28)
#define GPIO_Encoder_PIN_Forward_Left_A_PIN                     (DL_GPIO_PIN_28)
#define GPIO_Encoder_PIN_Forward_Left_A_IOMUX                     (IOMUX_PINCM3)
/* Defines for PIN_Forward_Left_B: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_Encoder_PIN_Forward_Left_B_PIN                     (DL_GPIO_PIN_31)
#define GPIO_Encoder_PIN_Forward_Left_B_IOMUX                     (IOMUX_PINCM6)
/* Port definition for Pin Group GPIO_MOTOR */
#define GPIO_MOTOR_PORT                                                  (GPIOB)

/* Defines for PIN_AIN1: GPIOB.0 with pinCMx 12 on package pin 47 */
#define GPIO_MOTOR_PIN_AIN1_PIN                                  (DL_GPIO_PIN_0)
#define GPIO_MOTOR_PIN_AIN1_IOMUX                                (IOMUX_PINCM12)
/* Defines for PIN_AIN2: GPIOB.16 with pinCMx 33 on package pin 4 */
#define GPIO_MOTOR_PIN_AIN2_PIN                                 (DL_GPIO_PIN_16)
#define GPIO_MOTOR_PIN_AIN2_IOMUX                                (IOMUX_PINCM33)
/* Defines for PIN_BIN1: GPIOB.15 with pinCMx 32 on package pin 3 */
#define GPIO_MOTOR_PIN_BIN1_PIN                                 (DL_GPIO_PIN_15)
#define GPIO_MOTOR_PIN_BIN1_IOMUX                                (IOMUX_PINCM32)
/* Defines for PIN_BIN2: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_MOTOR_PIN_BIN2_PIN                                 (DL_GPIO_PIN_17)
#define GPIO_MOTOR_PIN_BIN2_IOMUX                                (IOMUX_PINCM43)
/* Port definition for Pin Group GPIO_GRAY_SERIAL */
#define GPIO_GRAY_SERIAL_PORT                                            (GPIOA)

/* Defines for PIN_CLK: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_GRAY_SERIAL_PIN_CLK_PIN                            (DL_GPIO_PIN_24)
#define GPIO_GRAY_SERIAL_PIN_CLK_IOMUX                           (IOMUX_PINCM54)
/* Defines for PIN_FOWARD_DAT: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_GRAY_SERIAL_PIN_FOWARD_DAT_PIN                      (DL_GPIO_PIN_1)
#define GPIO_GRAY_SERIAL_PIN_FOWARD_DAT_IOMUX                     (IOMUX_PINCM2)
/* Port definition for Pin Group GPIO_COL */
#define GPIO_COL_PORT                                                    (GPIOA)

/* Defines for COL1: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_COL_COL1_PIN                                       (DL_GPIO_PIN_25)
#define GPIO_COL_COL1_IOMUX                                      (IOMUX_PINCM55)
/* Defines for COL2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define GPIO_COL_COL2_PIN                                        (DL_GPIO_PIN_8)
#define GPIO_COL_COL2_IOMUX                                      (IOMUX_PINCM19)
/* Defines for COL3: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_COL_COL3_PIN                                       (DL_GPIO_PIN_26)
#define GPIO_COL_COL3_IOMUX                                      (IOMUX_PINCM59)
/* Defines for COL4: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_COL_COL4_PIN                                       (DL_GPIO_PIN_27)
#define GPIO_COL_COL4_IOMUX                                      (IOMUX_PINCM60)
/* Defines for ROW1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_ROW_ROW1_PORT                                               (GPIOB)
#define GPIO_ROW_ROW1_PIN                                       (DL_GPIO_PIN_24)
#define GPIO_ROW_ROW1_IOMUX                                      (IOMUX_PINCM52)
/* Defines for ROW2: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_ROW_ROW2_PORT                                               (GPIOB)
#define GPIO_ROW_ROW2_PIN                                       (DL_GPIO_PIN_18)
#define GPIO_ROW_ROW2_IOMUX                                      (IOMUX_PINCM44)
/* Defines for ROW3: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_ROW_ROW3_PORT                                               (GPIOA)
#define GPIO_ROW_ROW3_PIN                                       (DL_GPIO_PIN_18)
#define GPIO_ROW_ROW3_IOMUX                                      (IOMUX_PINCM40)
/* Defines for ROW4: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_ROW_ROW4_PORT                                               (GPIOA)
#define GPIO_ROW_ROW4_PIN                                       (DL_GPIO_PIN_17)
#define GPIO_ROW_ROW4_IOMUX                                      (IOMUX_PINCM39)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_MOTOR_init(void);
void SYSCFG_DL_TIMER_CarCTRL_init(void);
void SYSCFG_DL_TIMER_CarCTRL_Alternative_init(void);
void SYSCFG_DL_TIMER_DingShiQi_init(void);
void SYSCFG_DL_TIMER_ShengGuang_init(void);
void SYSCFG_DL_TIMER_JiaJianSu_init(void);
void SYSCFG_DL_I2C_MPU6050_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
