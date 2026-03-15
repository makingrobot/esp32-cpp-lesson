#include "config.h"
#if BOARD_LESSON102_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define SD_CLK_PIN                          GPIO_NUM_3
#define SD_MOSI_PIN                         GPIO_NUM_4
#define SD_MISO_PIN                         GPIO_NUM_5
#define SD_CS_PIN                           GPIO_NUM_2

#define MIC_BCLK_PIN                        GPIO_NUM_17
#define MIC_WS_PIN                          GPIO_NUM_18
#define MIC_DIN_PIN                         GPIO_NUM_48

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif