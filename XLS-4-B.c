#include "ti_msp_dl_config.h"
#include "key.h"
#include "oled.h"
#include "motor.h"
#include "gray_sensor.h"
#include "board.h"
#include <stdio.h>
#include "bsp_mpu6050.h"
#include "inv_mpu.h"

void System_Init();
void GuanDao0(float expect_yaw, uint8_t dir);
void GuanDao1(float expect_yaw);
void GuanDao2(float expect_yaw);
void GuanDao3(float expect_yaw);
void GuanDao4(float expect_yaw);
void ShengGuang(void);

// 编码器转动计数----一圈大概20*13=260
volatile int32_t Forward_Right_Count = 0;
volatile int32_t Forward_Left_Count = 0;

// 灰度传感器数据
uint8_t sensor_data = 0;
uint8_t sensor[8] = {0};

// 小车控制巡线所需变量
volatile int BaseSpeed = 27;
volatile int MaxSpeed = 35;
volatile int Duty_L = 0, Duty_R = 0;
volatile uint8_t stop_flag = 0; 
volatile uint8_t wandao_sudu = 0; // 0：快速弯道    1：慢速弯道
volatile uint8_t jiajiansu_count = 0;
volatile uint8_t jiasu_flag = 0;

// UART参数
volatile uint8_t Uart_Data = 0;
volatile uint8_t Serial_RxFlag = 0;
uint8_t Serial_GetRxFlag(void);

// 陀螺仪参数
volatile uint8_t Uart_Tuoluoyi = 0;
volatile uint8_t tuoluoyi_rxflag = 0;
uint8_t Tuoluoyi_GetRxFlag(void);

// mpu6050
volatile uint8_t status;
volatile uint8_t ret = 1;
volatile float yaw_origin=0, YAW_ORIGIN=0;          
float pitch=0,roll=0,yaw=0;
float yaw_show=0;

// timer定时器：2s
volatile uint8_t timer_count = 0;

// 按键值
uint8_t key_num = 0;

int main(void)
{
    SYSCFG_DL_init();

    System_Init();
        
    uint8_t ret = 1;
          
    float pitch=0,roll=0,yaw=0;

    while (1) 
    {   
        key_num = key_read();
        OLED_ShowString(0, 2, "key_num:");
        OLED_ShowNum(88, 2, key_num, 2, 16);
        status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值
        if( status == 0 )
        {// 输出陀螺仪偏航角值,等待稳定后再按键
            OLED_ShowString(0, 0, "y:");
            if (yaw<0) {
                yaw_origin = -yaw;
                OLED_ShowString(16, 0, "-");
            }
            else {
                yaw_origin = yaw;
                OLED_ShowString(16, 0, " ");
            }
            OLED_ShowNum(24, 0, (int)yaw_origin, 3, 16);
        }
        switch (key_num) 
        {// 按键值
            case 1:
            {// 第一问
                yaw_origin = yaw;
                GuanDao1(0);
                Motor_Off();
                ShengGuang();
                break;
            }
            case 5:
            {// 第二问
                BaseSpeed = 18;
                MaxSpeed = 25;
                wandao_sudu = 1;
                // 第一段线
                YAW_ORIGIN = yaw;
                yaw_origin = yaw;
                GuanDao1(2);
                OLED_Clear();
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                NVIC_DisableIRQ(I2C_MPU6050_INST_INT_IRQN);
                BaseSpeed = 18;
                MaxSpeed = 25;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 0)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){}// 如果还有黑线，就保持灰度寻迹
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();
                // Motor_Off();
                

                // 回正
                yaw_origin = yaw_origin + 180;

                // 第三段线
                NVIC_EnableIRQ(I2C_MPU6050_INST_INT_IRQN);
                BaseSpeed = 18;
                MaxSpeed = 25;
                GuanDao2(3);            
                OLED_Clear();
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                NVIC_DisableIRQ(I2C_MPU6050_INST_INT_IRQN);
                BaseSpeed = 18;
                MaxSpeed = 25;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 1) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
                ShengGuang();

                //小车停
                DL_TimerG_stopCounter(PWM_MOTOR_INST);
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                Motor_Off();
                OLED_Clear();
                OLED_ShowString(2, 2, "I have stop!");
            }
            case 9:
            {// 第三问
                // 第一段线
                YAW_ORIGIN = yaw;
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                // int a = DL_Timer_getLoadValue(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 0) {
                    GuanDao1(-37);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(-10, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 1)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 2)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(43);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 3) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();
                Set_Speed(0, -2);

                //小车停
                DL_TimerG_stopCounter(PWM_MOTOR_INST);
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                Set_Speed(0, -2);
                delay_cycles(CPUCLK_FREQ/3);
                Motor_Off();
                OLED_Clear();
                OLED_ShowString(2, 2, "I have stop!");
                break;
            }
            case 13:
            {// 第四问
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 45999);
/////////////////////////////////////////////  第一圈  ////////////////////////////////////////////
                // 第一段线
                YAW_ORIGIN = yaw;
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                // int a = DL_Timer_getLoadValue(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 0) {
                    GuanDao1(-37);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(-10, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 1)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 2)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(43);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 3) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();
                Set_Speed(0, -2);

//////////////////////////////////////// 第二圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 4) {
                    GuanDao1(-37);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(-10, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 5)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 6) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(43);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 7) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();
                Set_Speed(0, -2);

//////////////////////////////////////// 第三圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 8) {
                    GuanDao1(-37);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(-10, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 9)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 10) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(43);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 11) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();
                Set_Speed(0, -2);

//////////////////////////////////////// 第四圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 12) {
                    GuanDao1(-37);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(-10, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 13)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 27;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 14) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(43);
                }
                
                OLED_Clear();

                //回正
                GuanDao0(5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 30;
                MaxSpeed = 40;
                NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                DL_TimerG_startCounter(TIMER_CarCTRL_INST);
                while (timer_count == 15) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                ShengGuang();

                //小车停
                DL_TimerG_stopCounter(PWM_MOTOR_INST);
                DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
                Set_Speed(0, -2);
                delay_cycles(CPUCLK_FREQ/3);
                Motor_Off();
                OLED_Clear();
                OLED_ShowString(2, 2, "I have stop!");
                break;
            }
            // case 2:
            // {// 
            //     wandao_sudu = 1;
            //     delay_cycles(CPUCLK_FREQ);
            //     NVIC_DisableIRQ(I2C_MPU6050_INST_INT_IRQN);
            //     BaseSpeed = 20;
            //     MaxSpeed = 30;
            //     NVIC_EnableIRQ(TIMER_CarCTRL_INST_INT_IRQN);
            //     DL_TimerG_startCounter(TIMER_CarCTRL_INST);
            //     while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
            //     DL_TimerG_stopCounter(PWM_MOTOR_INST);
            //     DL_TimerG_stopCounter(TIMER_CarCTRL_INST);
            //     ShengGuang();
            //     Set_Speed(0, -2);
            //     delay_cycles(CPUCLK_FREQ/5);
            //     Motor_Off();
            //     OLED_Clear();
            //     OLED_ShowString(2, 2, "I have stop!");
            //     break;
            // }

            // case 4:
            // {// 回正测试
            //     yaw_origin = yaw;
            //     GuanDao0(40, 1);
            //     printf("okokokokokokok");
            // }
            
            case 2:
            {// 开环加速度
                YAW_ORIGIN = yaw;
                delay_cycles(CPUCLK_FREQ);                
/////////////////////////////////////////////  第一圈  ////////////////////////////////////////////
                // 第一段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN; 
                while (timer_count == 0) 
                {
                    GuanDao3(-40);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                
                OLED_Clear();

                //回正
                GuanDao0(-2, 1);
                ShengGuang();

                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 1)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 2)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao4(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                ShengGuang();

                //回正
                GuanDao0(-5, 0);
                
                
                // 第四段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 3) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);

/////////////////////////////////////////////  第二圈  ////////////////////////////////////////////
                // 第一段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN; 
                while (timer_count == 4) 
                {
                    GuanDao3(-40);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                
                OLED_Clear();

                //回正
                GuanDao0(-2, 1);
                ShengGuang();

                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 5)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 6)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao4(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                ShengGuang();

                //回正
                GuanDao0(-5, 0);
                
                
                // 第四段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 7) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);
/////////////////////////////////////////////  第三圈  ////////////////////////////////////////////
                // 第一段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN; 
                while (timer_count == 8) 
                {
                    GuanDao3(-40);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                
                OLED_Clear();

                //回正
                GuanDao0(-2, 1);
                ShengGuang();

                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 9)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 10)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao4(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                ShengGuang();

                //回正
                GuanDao0(-5, 0);
                        
                // 第四段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 11) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);
/////////////////////////////////////////////  第四圈  ////////////////////////////////////////////
                // 第一段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN; 
                while (timer_count == 12) 
                {
                    GuanDao3(-40);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                
                OLED_Clear();

                //回正
                GuanDao0(-2, 1);
                ShengGuang();

                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 13)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 25999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 14)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao4(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                ShengGuang();
                
                //回正
                GuanDao0(-5, 0);
                
                // 第四段线
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 35999);
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 15) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);

                //小车停
                DL_TimerG_stopCounter(PWM_MOTOR_INST);
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_Alternative_INST_INT_IRQN);
                Set_Speed(0, -2);
                delay_cycles(CPUCLK_FREQ/3);
                Motor_Off();
                OLED_Clear();
                OLED_ShowString(2, 2, "I have stop!");

                break;
            }

            case 4:
            {// 第四问 快速
                DL_Timer_setLoadValue(TIMER_DingShiQi_INST, 31999);
/////////////////////////////////////////////  第一圈  ////////////////////////////////////////////
                // 第一段线
                YAW_ORIGIN = yaw;
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;  
                yaw_origin = YAW_ORIGIN;

                while (timer_count == 0) {
                    GuanDao1(-38);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                Set_Speed(0, -5);
                Set_Speed(1, -5);
                
                OLED_Clear();

                //回正
                GuanDao0(-2, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 1)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                printf("next state");
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 2)
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(-5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 3) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);

//////////////////////////////////////// 第二圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 4) {
                    GuanDao1(-38);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(2, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 5)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 6) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(-5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 7) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    printf("%d\r\r", sensor_data);
                }
                printf("next state");printf("%d\r\r", sensor_data);
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                printf("next line");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);

//////////////////////////////////////// 第三圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 8) {
                    GuanDao1(-38);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(2, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 9)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 10) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(-5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 11) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();
                Set_Speed(0, -5);

//////////////////////////////////////// 第四圈 ////////////////////////////////////////////
                // 第一段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);  
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = YAW_ORIGIN;
                while (timer_count == 12) {
                    GuanDao1(-38);
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(2, 1);
                ShengGuang();

                // 第二段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                OLED_ShowString(0, 2, "second begin");
                while(timer_count == 13)
                {// 如果还没到下一个状态时
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255)
                {// 如果还有黑线，就保持灰度寻迹 
                }
                OLED_ShowString(0, 2, "second stop");
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                // 第三段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 33;
                MaxSpeed = 35;
                yaw_origin = yaw_origin + 180;
                while (timer_count == 14) 
                {// 如果还在第三段线耗时太少
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                    GuanDao2(44);
                }
                
                OLED_Clear();
                Set_Speed(0, -5);
                Set_Speed(1, -5);

                //回正
                GuanDao0(-5, 0);
                ShengGuang();
                
                // 第四段线
                DL_TimerG_startCounter(TIMER_DingShiQi_INST);
                BaseSpeed = 35;
                MaxSpeed = 45;
                DL_TimerG_startCounter(TIMER_CarCTRL_Alternative_INST);
                while (timer_count == 15) {
                    OLED_ShowNum(120, 0, timer_count, 1, 16);
                }
                while(sensor_data!=255){} // 如果还有黑线，就保持灰度寻迹
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                ShengGuang();

                //小车停
                DL_TimerG_stopCounter(PWM_MOTOR_INST);
                DL_TimerG_stopCounter(TIMER_CarCTRL_Alternative_INST);
                NVIC_DisableIRQ(TIMER_CarCTRL_Alternative_INST_INT_IRQN);
                Set_Speed(0, -2);
                delay_cycles(CPUCLK_FREQ/3);
                Motor_Off();
                OLED_Clear();
                OLED_ShowString(2, 2, "I have stop!");
                break;
            }
            default: break;
        }                
    }
}


/**** 外设初始化 ****/
void System_Init()
{
    // MPU6050初始化
    NVIC_EnableIRQ(I2C_MPU6050_INST_INT_IRQN);
    OLED_ShowString(0, 2, "ok");	
	MPU6050_Init();
    mpu_dmp_init();
    OLED_ShowString(0, 4, "ok");

    // OLED初始化
    OLED_Init();
    OLED_Clear();

    // 电机PWM初始化
    DL_TimerG_startCounter(PWM_MOTOR_INST);

    // 编码器中断使能
    NVIC_EnableIRQ(GPIO_Encoder_INT_IRQN);  

    // 定时器中断
    NVIC_EnableIRQ(TIMER_DingShiQi_INST_INT_IRQN);   

    // 加减速定时器中断
    NVIC_EnableIRQ(TIMER_JiaJianSu_INST_INT_IRQN);
    
    // 声光定时器中断
    NVIC_EnableIRQ(TIMER_ShengGuang_INST_INT_IRQN);

    // UART初始化
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    // 替代灰度传感器定时器中断
    NVIC_EnableIRQ(TIMER_CarCTRL_Alternative_INST_INT_IRQN);
}

/**** 无线区域小车移动 ****/
void GuanDao1(float expect_yaw)
{
    OLED_Clear();
    OLED_ShowString(64, 0, "y_o:");
    OLED_ShowNum(104, 0, (int)yaw_origin, 3, 16);                  
    sensor_data = 255;
    while(sensor_data == 255)
    {//灰度传感器都是1
        //获取灰度传感器值
        OLED_ShowBasicBoard();
        sensor_data = gray_serial_forward_read();
        extractSensorData(sensor_data, sensor);
        status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值   
        if( status == 0 )
        {//显示yaw值 
            OLED_ShowString(0, 0, "y:");
            yaw = yaw - yaw_origin; // 消除零偏
            yaw_show = yaw;
            TuoLuoYi_Ctrl_PID(expect_yaw, yaw);
            if (yaw_show<0) {
                yaw_show = -yaw_show;
                OLED_ShowString(16, 0, "-");
            }
            else {
                OLED_ShowString(16, 0, " ");
            }
            OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
        }                   
    }
}

void GuanDao2(float expect_yaw)
{
    OLED_Clear();                 
    sensor_data = 255;
    while(sensor_data == 255)
    {//灰度传感器都是1
        //获取灰度传感器值
        OLED_ShowBasicBoard();
        sensor_data = gray_serial_forward_read();
        extractSensorData(sensor_data, sensor);
        status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值   
        if( status == 0 )
        {//显示yaw值 
            OLED_ShowString(0, 0, "y:");
            yaw = yaw - yaw_origin; // 消除零偏
            if(yaw < -180){
                yaw = 360 + yaw;
            }
            // printf("yaw:%f\r\r", yaw);
            yaw_show = yaw;
            TuoLuoYi_Ctrl_PID(expect_yaw, yaw);
            if (yaw_show<0) {
                yaw_show = -yaw_show;
                OLED_ShowString(16, 0, "-");
            }
            else {
                OLED_ShowString(16, 0, " ");
            }
            OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
        }
                        
    }
}

void GuanDao3(float expect_yaw)
{
    DL_Timer_setLoadValue(TIMER_JiaJianSu_INST, 7999);
    DL_Timer_startCounter(TIMER_JiaJianSu_INST);
    OLED_Clear();
    OLED_ShowString(64, 0, "y_o:");
    OLED_ShowNum(104, 0, (int)yaw_origin, 3, 16);                  
    sensor_data = 255;
    while(sensor_data == 255)
    {//灰度传感器都是1
        //获取灰度传感器值
        if (jiajiansu_count == 1) 
        {// 如果已经转过弯, 加速
            BaseSpeed = 50;
            MaxSpeed = 60;
            jiasu_flag = 1;
            DL_Timer_setLoadValue(TIMER_JiaJianSu_INST, 19999);//1s
            DL_Timer_startCounter(TIMER_JiaJianSu_INST);
        }
        else if(jiajiansu_count == 2)
        {// 减速
            BaseSpeed = 32;
            MaxSpeed = 35;
            jiasu_flag = 0;
        }
        OLED_ShowBasicBoard();
        sensor_data = gray_serial_forward_read();
        extractSensorData(sensor_data, sensor);
        status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值   
        if( status == 0 )
        {//显示yaw值 
            OLED_ShowString(0, 0, "y:");
            yaw = yaw - yaw_origin; // 消除零偏
            yaw_show = yaw;
            TuoLuoYi_Ctrl_PID(expect_yaw, yaw);
            if (yaw_show<0) {
                yaw_show = -yaw_show;
                OLED_ShowString(16, 0, "-");
            }
            else {
                OLED_ShowString(16, 0, " ");
            }
            OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
        }  

    }
    jiajiansu_count = 0;
}

void GuanDao4(float expect_yaw)
{
    DL_Timer_setLoadValue(TIMER_JiaJianSu_INST, 7999);
    DL_Timer_startCounter(TIMER_JiaJianSu_INST);
    OLED_Clear();                 
    sensor_data = 255;
    while(sensor_data == 255)
    {//灰度传感器都是1
        //获取灰度传感器值
        if (jiajiansu_count == 1) 
        {// 如果已经转过弯, 加速
            BaseSpeed = 50;
            MaxSpeed = 60;
            jiasu_flag = 1;
            DL_Timer_setLoadValue(TIMER_JiaJianSu_INST, 19999);//1s
            DL_Timer_startCounter(TIMER_JiaJianSu_INST);
        }
        else if(jiajiansu_count == 2)
        {// 减速
            BaseSpeed = 32;
            MaxSpeed = 35;
            jiasu_flag = 0;
        }
        OLED_ShowBasicBoard();
        sensor_data = gray_serial_forward_read();
        extractSensorData(sensor_data, sensor);
        status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值   
        if( status == 0 )
        {//显示yaw值 
            OLED_ShowString(0, 0, "y:");
            yaw = yaw - yaw_origin; // 消除零偏
            if(yaw < -180){
                yaw = 360 + yaw;
            }
            // printf("yaw:%f\r\r", yaw);
            yaw_show = yaw;
            TuoLuoYi_Ctrl_PID(expect_yaw, yaw);
            if (yaw_show<0) {
                yaw_show = -yaw_show;
                OLED_ShowString(16, 0, "-");
            }
            else {
                OLED_ShowString(16, 0, " ");
            }
            OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
        }
                         
    }
    jiajiansu_count = 0;
}

/**** 小车回正 ****/
void GuanDao0(float expect_yaw, uint8_t dir)
{
    OLED_ShowNum(80, 0, yaw_origin, 3, 16);
    OLED_ShowString(0, 0, "y:");     
    if (dir == 1) 
    {// 转动右轮 
        Set_Speed(0, 1);
        Set_Speed(1, 15);
        while(yaw <= expect_yaw)
        {   
            status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值 
            if( status == 0 )
            {//显示yaw值
                OLED_ShowString(0, 0, "y:");
                yaw = yaw - yaw_origin; // 消除零偏
                yaw_show = yaw;
                if (yaw_show<0) {
                    yaw_show = -yaw_show;
                    OLED_ShowString(16, 0, "-");
                }
                else {
                    OLED_ShowString(16, 0, " ");
                }
                OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
            }
        } 
    }
    else if(dir == 0)
    {// 转动左轮
        while (yaw >= expect_yaw) 
        {
            Set_Speed(0, 15);
            Set_Speed(1, 1);
            status = mpu_dmp_get_data(&pitch, &roll, &yaw);// 读一次陀螺仪值   
            if( status == 0 )
            {//显示yaw值 
                OLED_ShowString(0, 0, "y:");
                yaw = yaw - yaw_origin; // 消除零偏
                if(yaw < -180){
                    yaw = 360 + yaw;
                }
                yaw_show = yaw;
                if (yaw_show<0) {
                    yaw_show = -yaw_show;
                    OLED_ShowString(16, 0, "-");
                }
                else {
                    OLED_ShowString(16, 0, " ");
                }
                OLED_ShowNum(24, 0, (int)yaw_show, 3, 16);
            }
        }
        printf("yihuizheng                         ");
    }                         
}

/**** 替换的灰度传感器控制小车方向 ****/
void TIMER_CarCTRL_Alternative_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_CarCTRL_Alternative_INST)) {
        case DL_TIMER_IIDX_ZERO:
            OLED_ShowBasicBoard();
            //获取灰度传感器值
            sensor_data = gray_serial_forward_read();
            extractSensorData(sensor_data, sensor);
            GetErrorandA(); // 得到偏差
            // 控制小车运行
            Gray_Sensor_Ctrl_PID_Alternative();// 控制轮速
            break;
        default:
            break;
    }
}

/**** 小车加减速定时器 ****/
void TIMER_JiaJianSu_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_JiaJianSu_INST)) {
        case DL_TIMER_IIDX_ZERO:
            jiajiansu_count++;
            break;
        default:
            break;
    }
}

/**** 小车控制 ****/
void TIMER_CarCTRL_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_CarCTRL_INST)) {
        case DL_TIMER_IIDX_ZERO:
            OLED_ShowBasicBoard();
            //获取灰度传感器值
            sensor_data = gray_serial_forward_read();
            extractSensorData(sensor_data, sensor);
            GetErrorandA(); // 得到偏差
            // 控制小车运行
            if (wandao_sudu == 0) {
                Gray_Sensor_Ctrl_PID();// 控制轮速
            }
            else {
                Gray_Sensor_Ctrl_Mansu_PID();
            }

            break;
        default:
            break;
    }
}

/**** 外部中断读取编码器的值 ****/
void GROUP1_IRQHandler(void)
{
    int32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, GPIO_Encoder_PIN_Forward_Left_A_PIN | GPIO_Encoder_PIN_Forward_Right_A_PIN);

    if (gpioA & GPIO_Encoder_PIN_Forward_Right_A_PIN) //前右轮A相上升沿触发中断
    {
        if(DL_GPIO_readPins(GPIO_Encoder_PORT, GPIO_Encoder_PIN_Forward_Right_B_PIN))//读一下前右轮B相状态
            Forward_Right_Count--;
        else 
            Forward_Right_Count++;
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PORT, GPIO_Encoder_PIN_Forward_Right_A_PIN);
    }

    if (gpioA & GPIO_Encoder_PIN_Forward_Left_A_PIN) // 前左A相上升沿触发中断
    {
        if(DL_GPIO_readPins(GPIO_Encoder_PORT, GPIO_Encoder_PIN_Forward_Left_B_PIN))//读取前左轮B相状态
            Forward_Left_Count++;
        else
            Forward_Left_Count--;
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PORT, GPIO_Encoder_PIN_Forward_Left_A_PIN);
    }
}

/**** 速度调试串口接收中断 ****/
void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            Uart_Data = DL_UART_Main_receiveData(UART_0_INST); 
            Serial_RxFlag = 1;
            break;
        default:
            break;
    }
}

/**** 判断速度调试串口是否接受完了一帧数据 ****/
uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)			//如果标志位为1
	{
		Serial_RxFlag = 0;
		return 1;					//则返回1，并自动清零标志位
	}
	return 0;						//如果标志位为0，则返回0
}

/**** 定时器中断 ****/
void TIMER_DingShiQi_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_DingShiQi_INST)) {
        case DL_TIMER_IIDX_ZERO:
            timer_count++;
            break;
        default:
            break;
    }
}

/**** 声光定时器中断 ****/
void TIMER_ShengGuang_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_ShengGuang_INST)) {
        case DL_TIMER_IIDX_ZERO:
            DL_GPIO_setPins(GPIO_BEEP_PORT, GPIO_BEEP_PIN_0_PIN);
            DL_GPIO_clearPins(GPIO_MYLED_PORT, GPIO_MYLED_PIN_LED_PIN);
            break;
        default:
            break;
    }
}

/**** 声光提示 ****/
void ShengGuang(void)
{
    DL_GPIO_clearPins(GPIO_BEEP_PORT, GPIO_BEEP_PIN_0_PIN);
    DL_GPIO_setPins(GPIO_MYLED_PORT, GPIO_MYLED_PIN_LED_PIN);
    DL_Timer_startCounter(TIMER_ShengGuang_INST);
}