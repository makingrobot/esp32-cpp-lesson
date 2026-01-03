#include "config.h"
#if BOARD_LESSON21_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4
#define RGB_LED_R_PIN                       GPIO_NUM_32
#define RGB_LED_G_PIN                       GPIO_NUM_23
#define RGB_LED_B_PIN                       GPIO_NUM_33

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 0
#define CONFIG_USE_LED_RGB                 1
#define CONFIG_USE_LED_WS2812               0

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif