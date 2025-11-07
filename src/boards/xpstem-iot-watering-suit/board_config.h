#include "config.h"
#if BOARD_XPSTEM_IOT_WATERING_SUIT == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#define I2C_SCL_PIN                 GPIO_NUM_40   
#define I2C_SDA_PIN                 GPIO_NUM_41

// 三按键模块
#define BUTTON_1_PIN            GPIO_NUM_1  
#define BUTTON_2_PIN            GPIO_NUM_0
#define BUTTON_3_PTN            GPIO_NUM_47

#endif // _BOARD_CONFIG_H

#endif
