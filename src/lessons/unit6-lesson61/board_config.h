#include "config.h"
#if BOARD_LESSON61 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

//*******************************************************************
// 引脚定义

#define BUILTIN_LED_PIN                     GPIO_NUM_4
#define WS2812_PIN                          GPIO_NUM_5
#define MANUAL_BUTTON_PIN                   GPIO_NUM_39

#define TOUCH_1_PIN                         GPIO_NUM_2
#define TOUCH_2_PIN                         GPIO_NUM_34

#define DHT11_PIN                           GPIO_NUM_25
#define IR_SENSOR_PIN                       GPIO_NUM_35

#define RELAY_PIN                           GPIO_NUM_26

//**********************************************************************
// 配置定义

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_BOARD_CONFIG_H

#endif