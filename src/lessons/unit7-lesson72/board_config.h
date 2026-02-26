#include "config.h"
#if BOARD_LESSON72 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4

// OLED
#define I2C_SCL_PIN                         GPIO_NUM_22  //  
#define I2C_SDA_PIN                         GPIO_NUM_21  //  
#define OLED_I2C_ADDRESS                    0x3D
#define DISPLAY_WIDTH                       128
#define DISPLAY_HEIGHT                      64

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

// 图形化
#define CONFIG_USE_DISPLAY                  1   // 显示
#define CONFIG_USE_U8G2                     1   // U8G2

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif