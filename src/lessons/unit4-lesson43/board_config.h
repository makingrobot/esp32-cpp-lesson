#include "config.h"
#if APP_LESSON43 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4
#define WS2812_PIN                          GPIO_NUM_5

#define TOUCH_1_PIN                         GPIO_NUM_2
#define TOUCH_2_PIN                         GPIO_NUM_34
#define DHT11_PIN                           GPIO_NUM_25
#define IR_SENSOR_PIN                       GPIO_NUM_35


#endif //_BOARD_CONFIG_H

#endif