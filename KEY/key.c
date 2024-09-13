#include "key.h"
#include "oled.h"
#include "ti/driverlib/m0p/dl_core.h"

// 舵机comparevalue：往右和往下时增大，范围8750-9750，定时器频率50Hz
uint8_t key_scan(void)
{
    uint8_t Key_Flag = 0;
    DL_GPIO_clearPins(GPIO_COL_PORT, GPIO_COL_COL1_PIN |
            GPIO_COL_COL2_PIN |
            GPIO_COL_COL3_PIN |
            GPIO_COL_COL4_PIN);

    Key_Flag = ((GPIO_ROW_ROW1_PIN != DL_GPIO_readPins(GPIO_ROW_ROW1_PORT, GPIO_ROW_ROW1_PIN))  ||  
                (GPIO_ROW_ROW2_PIN != DL_GPIO_readPins(GPIO_ROW_ROW2_PORT, GPIO_ROW_ROW2_PIN))  ||  
                (GPIO_ROW_ROW3_PIN != DL_GPIO_readPins(GPIO_ROW_ROW3_PORT, GPIO_ROW_ROW3_PIN))  || 
                (GPIO_ROW_ROW4_PIN != DL_GPIO_readPins(GPIO_ROW_ROW4_PORT, GPIO_ROW_ROW4_PIN)) ) ;


    return(Key_Flag);
}

int8_t key_read(void)
{
    int8_t Key_Num = 0;
    //uint32_t Key_Temp = 0;

    if(key_scan()){
        delay_cycles(CPUCLK_FREQ/100);
        if(key_scan()){
            DL_GPIO_setPins(GPIO_COL_PORT, GPIO_COL_COL2_PIN |
                        GPIO_COL_COL3_PIN |
                        GPIO_COL_COL4_PIN);
            DL_GPIO_clearPins(GPIO_COL_PORT, GPIO_COL_COL1_PIN );
            // Key_Temp = DL_GPIO_readPins(GPIO_ROW_PORT,GPIO_ROW_ROW1_PIN |
            //                      GPIO_ROW_ROW2_PIN |
            //                      GPIO_ROW_ROW3_PIN |
            //                      GPIO_ROW_ROW4_PIN );
            // if((Key_Temp & GPIO_ROW_ROW1_PIN) == 0) return 1 ;
            // if((Key_Temp & GPIO_ROW_ROW2_PIN) == 0) return 5 ;
            // if((Key_Temp & GPIO_ROW_ROW3_PIN) == 0) return 9 ;
            // if((Key_Temp & GPIO_ROW_ROW4_PIN) == 0) return 13 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW1_PORT, GPIO_ROW_ROW1_PIN)) return 1 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW2_PORT, GPIO_ROW_ROW2_PIN)) return 5 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW3_PORT, GPIO_ROW_ROW3_PIN)) return 9 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW4_PORT, GPIO_ROW_ROW4_PIN)) return 13 ;

            delay_cycles(20);

            DL_GPIO_setPins(GPIO_COL_PORT, GPIO_COL_COL1_PIN |
                                    GPIO_COL_COL3_PIN |
                                    GPIO_COL_COL4_PIN);
            DL_GPIO_clearPins(GPIO_COL_PORT, GPIO_COL_COL2_PIN );
            // Key_Temp = DL_GPIO_readPins(GPIO_ROW_PORT,GPIO_ROW_ROW1_PIN |
            //                                  GPIO_ROW_ROW2_PIN |
            //                                  GPIO_ROW_ROW3_PIN |
            //                                  GPIO_ROW_ROW4_PIN );
            // if((Key_Temp & GPIO_ROW_ROW1_PIN) == 0) return 2 ;
            // if((Key_Temp & GPIO_ROW_ROW2_PIN) == 0) return 6 ;
            // if((Key_Temp & GPIO_ROW_ROW3_PIN) == 0) return 10 ;
            // if((Key_Temp & GPIO_ROW_ROW4_PIN) == 0) return 14 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW1_PORT, GPIO_ROW_ROW1_PIN)) return 2 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW2_PORT, GPIO_ROW_ROW2_PIN)) return 6 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW3_PORT, GPIO_ROW_ROW3_PIN)) return 10 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW4_PORT, GPIO_ROW_ROW4_PIN)) return 14 ;

            delay_cycles(20);

            DL_GPIO_setPins(GPIO_COL_PORT, GPIO_COL_COL1_PIN |
                                   GPIO_COL_COL2_PIN |
                                   GPIO_COL_COL4_PIN);
           DL_GPIO_clearPins(GPIO_COL_PORT, GPIO_COL_COL3_PIN );
        //    Key_Temp = DL_GPIO_readPins(GPIO_ROW_PORT,GPIO_ROW_ROW1_PIN |
        //                                     GPIO_ROW_ROW2_PIN |
        //                                     GPIO_ROW_ROW3_PIN |
        //                                     GPIO_ROW_ROW4_PIN );
        //   if((Key_Temp & GPIO_ROW_ROW1_PIN) == 0) return 3 ;
        //   if((Key_Temp & GPIO_ROW_ROW2_PIN) == 0) return 7 ;
        //   if((Key_Temp & GPIO_ROW_ROW3_PIN) == 0) return 11 ;
        //   if((Key_Temp & GPIO_ROW_ROW4_PIN) == 0) return 15 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW1_PORT, GPIO_ROW_ROW1_PIN)) return 3 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW2_PORT, GPIO_ROW_ROW2_PIN)) return 7 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW3_PORT, GPIO_ROW_ROW3_PIN)) return 11 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW4_PORT, GPIO_ROW_ROW4_PIN)) return 15 ;

          delay_cycles(20);

          DL_GPIO_setPins(GPIO_COL_PORT, GPIO_COL_COL1_PIN |
                                         GPIO_COL_COL2_PIN |
                                         GPIO_COL_COL3_PIN);
          DL_GPIO_clearPins(GPIO_COL_PORT, GPIO_COL_COL4_PIN );
        //   Key_Temp = DL_GPIO_readPins(GPIO_ROW_PORT,GPIO_ROW_ROW1_PIN |
        //                                             GPIO_ROW_ROW2_PIN |
        //                                             GPIO_ROW_ROW3_PIN |
        //                                             GPIO_ROW_ROW4_PIN );
        //   if((Key_Temp & GPIO_ROW_ROW1_PIN) == 0) return 4 ;
        //   if((Key_Temp & GPIO_ROW_ROW2_PIN) == 0) return 8 ;
        //   if((Key_Temp & GPIO_ROW_ROW3_PIN) == 0) return 12 ;
        //   if((Key_Temp & GPIO_ROW_ROW4_PIN) == 0) return 16 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW1_PORT, GPIO_ROW_ROW1_PIN)) return 4 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW2_PORT, GPIO_ROW_ROW2_PIN)) return 8 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW3_PORT, GPIO_ROW_ROW3_PIN)) return 12 ;
            if(!DL_GPIO_readPins(GPIO_ROW_ROW4_PORT, GPIO_ROW_ROW4_PIN)) return 16 ;

        }
    }

    return(Key_Num);

}
