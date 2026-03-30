#include "config.h"
#if BOARD_LESSON73_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

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


#endif //_BOARD_CONFIG_H

#endif