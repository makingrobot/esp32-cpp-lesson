#include "config.h"
#if BOARD_LESSON22_B == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4
#define WS2812_PIN                          GPIO_NUM_5

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_RGB                  0
#define CONFIG_USE_LED_WS2812               1

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif