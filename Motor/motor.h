#include "ti_msp_dl_config.h"

// 电机停转
void Motor_Off(void);

// 设置左右电机速度
void Set_Speed(int side, int duty);

// // 基于摄像头的小车位置控制PID
// void Camera_Position_Ctrl_P(int target_x, int current_x, int baseSpeed, int maxSpeed);

// 基于灰度传感器的控制小车位置PID
void Gray_Sensor_Ctrl_PID(void);
void Gray_Sensor_Ctrl_PID_Alternative(void);
void Gray_Sensor_Ctrl_Mansu_PID(void);

// 根据陀螺仪数据控制小车角度PID
void TuoLuoYi_Ctrl_PID(float expect_yaw, float current_yaw);

// 限幅函数
void XianFu(void);