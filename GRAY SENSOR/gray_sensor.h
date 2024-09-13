#ifndef GRAY_SENSOR_H
#define GRAY_SENSOR_H
#include "ti_msp_dl_config.h"

// 读灰度传感器的值
uint8_t gray_serial_forward_read();
// 灰度传感器值中零的数量
uint8_t NumofZero(void);
// 灰度传感器值—>error
void GetErrorandA(void);

// 从一个变量分离出所有的bit
void extractSensorData(uint8_t sensor_data, uint8_t sensor[8]);


#endif