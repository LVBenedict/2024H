#include "gray_sensor.h"
#include "oled.h"
#include "motor.h"

volatile int8_t error; // 灰度传感器传回来的error
volatile uint8_t a;
extern uint8_t stop_flag; // 停车标志位
extern uint8_t sensor[8]; // main.c中定义的灰度传感器值


/**** 读取灰度传感器数据 ****/
uint8_t gray_serial_forward_read(void)
{
    uint16_t ret = 0;
    uint8_t ret_8 = 0;
    for(int i = 0; i < 8; i++)
    {
        DL_GPIO_clearPins(GPIO_GRAY_SERIAL_PORT, GPIO_GRAY_SERIAL_PIN_CLK_PIN);//时钟下降沿读数
        delay_cycles(CPUCLK_FREQ/100000);//延时10us
        ret |= DL_GPIO_readPins(GPIO_GRAY_SERIAL_PORT, GPIO_GRAY_SERIAL_PIN_FOWARD_DAT_PIN) << i;
        DL_GPIO_setPins(GPIO_GRAY_SERIAL_PORT, GPIO_GRAY_SERIAL_PIN_CLK_PIN);//输出高电平让传感器更新数据
        delay_cycles(CPUCLK_FREQ/100000);//延时10us       
    }
    ret_8 = (ret >> 1) & 0xFF; 
    return ret_8;
}

/**** 从一个变量分离出所有的bit ****/
void extractSensorData(uint8_t sensor_data, uint8_t sensor[8]) 
{
    for (int i = 0; i < 8; i++) {
        sensor[i] = (sensor_data >> i) & 1;
    }
}

/**** 从sensor里得到error和a的值 ****/
void GetErrorandA(void)
{
    /********************************************* 巡线 ********************************************/
    if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 如果丢线
        stop_flag = 1;
    } 
    if ((sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1) 
     || (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)) 
    {// 线在中心，小车没偏
        error = 0; a = 0;
    }
    /********************************************* 偏右边 ******************************************/
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度小
        error = -4; a = 1;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度较小
        error = -5; a = 2;
    }
    else if (sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度适中
        error = -7; a = 3;
    }
    else if (sensor[0]==1 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度较大
        error = -9; a = 4;
    }
    else if (sensor[0]==0 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度大
        error = -11; a = 5;
    }
    else if (sensor[0]==0 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏右程度剧烈
        error = -13; a = 6;
    }

    /********************************************* 偏左边 ******************************************/ 
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==0 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏左程度小
        error = 4; a = 1;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==0 && sensor[6]==1 && sensor[7]==1)
    {// 小车偏左程度较小
        error = 5; a = 2;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==0 && sensor[6]==0 && sensor[7]==1)
    {// 小车偏左程度适中
        error = 7; a = 3;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==0 && sensor[7]==1)
    {// 小车偏左程度较大
        error = 9; a = 4;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==0 && sensor[7]==0)
    {// 小车偏左程度大
        error = 11; a = 5;
    }
    else if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==0)
    {// 小车偏左程度剧烈
        error = 13; a = 6;
    }

}






/**** 获取灰度传感器中零的数量 ****/
uint8_t NumofZero(void)
{
    uint8_t i = 0, count = 0;
    for(; i<8; ++i)
    {// 遍历sensor数组，查询零的数量，可判断是否到弯道和停车
        if (sensor[i] == 0) {
            count++;
        }
    }
    return count;
}
