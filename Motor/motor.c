#include "motor.h"
#include <stdio.h>

extern int Duty_L, Duty_R; //main.c中定义的左右轮PWM占空比
extern int8_t error; // gray_sensor.c中定义的灰度传感器error值
extern int BaseSpeed, MaxSpeed;// 基础期望速度
extern uint8_t jiasu_flag;

/*** 根据灰度传感器数据控制小车角度PID ****/
void Gray_Sensor_Ctrl_PID(void)
{// BaseSpeed = 18, MaxSpeed = 25: Position_KP = 0.5, Position_KI = 0, Position_KD = 8;
 // BaseSpeed = 25, MaxSpeed = 35: Position_KP = 0.6, Position_KI = 0, Position_KD = 8;
 // BaseSpeed = 35, MaxSpeed = 45: Position_KP = 0.9, Position_KI = 0, Position_KD = 15;
    float Position_KP_l = 0.5, Position_KI_l = 0, Position_KD_l = 120; 
    float Position_KP_r = 0.52, Position_KI_r = 0, Position_KD_r = 120; 
	static int Speed_chasu_l, Speed_chasu_r;
    static int8_t Integral_error, Last_error;
    Integral_error += error;
    Speed_chasu_l = Position_KP_l * error + Position_KI_l * Integral_error + Position_KD_l * (error - Last_error);
    Speed_chasu_r = Position_KP_r * error + Position_KI_r * Integral_error + Position_KD_r * (error - Last_error);
    Last_error = error;
    Duty_L = BaseSpeed + Speed_chasu_l;
    Duty_R = BaseSpeed - Speed_chasu_r;
    XianFu();
    Set_Speed(0, Duty_L); // 右边电机
    Set_Speed(1, Duty_R); // 左边电机
}

void Gray_Sensor_Ctrl_Mansu_PID(void)
{// BaseSpeed = 18, MaxSpeed = 25: Position_KP = 0.5, Position_KI = 0, Position_KD = 8;
 // BaseSpeed = 25, MaxSpeed = 35: Position_KP = 0.6, Position_KI = 0, Position_KD = 8;
 // BaseSpeed = 35, MaxSpeed = 45: Position_KP = 0.9, Position_KI = 0, Position_KD = 15;
    float Position_KP_l = 0.3, Position_KI_l = 0, Position_KD_l = 20;
    float Position_KP_r = 0.3, Position_KI_r = 0, Position_KD_r = 20;
	static int Speed_chasu_l, Speed_chasu_r;
    static int8_t Integral_error, Last_error;
    Integral_error += error;
    Speed_chasu_l = Position_KP_l * error + Position_KI_l * Integral_error + Position_KD_l * (error - Last_error);
    Speed_chasu_r = Position_KP_r * error + Position_KI_r * Integral_error + Position_KD_r * (error - Last_error);
    Last_error = error;
    Duty_L = BaseSpeed + Speed_chasu_l;
    Duty_R = BaseSpeed - Speed_chasu_r;
    XianFu();
    Set_Speed(0, Duty_L); // 右边电机
    Set_Speed(1, Duty_R); // 左边电机
}

void Gray_Sensor_Ctrl_PID_Alternative(void)
{
    float Position_KP_l = 0.35, Position_KI_l = 0, Position_KD_l = 200;
    float Position_KP_r = 0.4, Position_KI_r = 0, Position_KD_r = 200;
	static int Speed_chasu_l, Speed_chasu_r;
    static int8_t Integral_error, Last_error;
    Integral_error += error;
    Speed_chasu_l = Position_KP_l * error + Position_KI_l * Integral_error + Position_KD_l * (error - Last_error);
    Speed_chasu_r = Position_KP_r * error + Position_KI_r * Integral_error + Position_KD_r * (error - Last_error);
    Last_error = error;
    Duty_L = BaseSpeed + Speed_chasu_l;
    Duty_R = BaseSpeed - Speed_chasu_r;
    XianFu();
    Set_Speed(0, Duty_L); // 右边电机
    Set_Speed(1, Duty_R); // 左边电机
}

/**** 根据陀螺仪数据控制小车角度PID ****/
void TuoLuoYi_Ctrl_PID(float expect_yaw, float current_yaw)
{
    float Position_KP = 0.5, Position_KI = 0, Position_KD = 10;
	static int Speed_chasu;
    static int8_t error, Integral_error, Last_error;
    
    if (jiasu_flag == 1) {
        Position_KD = 20;
    }
    error = current_yaw - expect_yaw;
    Integral_error += error;
    
    Speed_chasu = Position_KP * error + Position_KI * Integral_error + Position_KD * (error - Last_error);
    Last_error = error;
    // printf("current:%f\r\n\r\n", current_yaw);
    // printf("expect:%f\r\n\r\n", expect_yaw);
    // printf("error:%d\r\n\r\n", error);
    Duty_L = BaseSpeed + Speed_chasu;
    Duty_R = BaseSpeed - Speed_chasu;
    XianFu();
    // printf("dutyl:%d\r\n\r\n", Duty_L);
    // printf("dutyr:%d\r\n\r\n", Duty_R);
    Set_Speed(0, Duty_L); // 右边电机
    Set_Speed(1, Duty_R); // 左边电机
}

/**** 限幅函数 ****/
void XianFu(void)
{
    if (Duty_L > MaxSpeed) // 尽量占空比不大于60%
        Duty_L = MaxSpeed;
    else if(Duty_L <= 0)// 本题只正转
        Duty_L = 1;
    if (Duty_R > MaxSpeed) // 尽量占空比不大于60%
        Duty_R = MaxSpeed;
    else if(Duty_R <= 0)// 本题只正转
        Duty_R = 1;
}

/**** 关闭电机 ****/
void Motor_Off(void)
{
    DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN1_PIN);
    DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN2_PIN);
    DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN1_PIN);
    DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN2_PIN);
}

/**** 设置左右电机速度 ****/
//side = 0:   左边电机    
//side = 1:   右边电机
void Set_Speed(int side, int duty)
{
    int compareValue = 0;
    if(side == 1)
    {//控制右边电机
        if(duty < 0)
        {//如果duty小于0，反转
            compareValue = 3199 - 3199 * (-duty/100.0);
            DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, GPIO_PWM_MOTOR_C0_IDX);
            DL_GPIO_setPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN2_PIN);
        }
        else if(duty > 0)
        {//正转
            compareValue = 3199 - 3199 * (duty/100.0);
            DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, GPIO_PWM_MOTOR_C0_IDX);
            DL_GPIO_setPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN2_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN1_PIN);
        }
        else 
        {//停止
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN2_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN2_PIN);
        }
    }
    else
    {// side = 0, 控制左边电机
        if(duty < 0)
        {//反转
            compareValue = 3199 - 3199 * (-duty/100.0);
            DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, GPIO_PWM_MOTOR_C1_IDX);
            DL_GPIO_setPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN2_PIN);
        }
        else if(duty > 0)
        {//正转
            compareValue = 3199 - 3199 * (duty/100.0);
            DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, DL_TIMER_CC_1_INDEX);
            DL_GPIO_setPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN2_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN1_PIN);
        }
        else 
        {//停止
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_AIN2_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PORT, GPIO_MOTOR_PIN_BIN2_PIN);
        }
    }
}
