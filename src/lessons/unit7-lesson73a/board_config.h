#include "config.h"
#if BOARD_LESSON73_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4

// ST7789
#define TFT_CS                              GPIO_NUM_17
#define TFT_RST                             GPIO_NUM_16
#define TFT_DC                              GPIO_NUM_15
#define TFT_MOSI                            GPIO_NUM_14
#define TFT_SCK                             GPIO_NUM_33
#define TFT_LED                             GPIO_NUM_32
#define TFT_MISO                            GPIO_NUM_23

#define DISPLAY_WIDTH                       320
#define DISPLAY_HEIGHT                      240
#define DISPLAY_INVERT_COLOR                true

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

#define CONFIG_USE_DISPLAY                  1   // 显示
#define CONFIG_USE_TFT_ESPI                 1

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif