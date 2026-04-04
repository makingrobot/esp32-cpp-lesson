#include "config.h"
#if APP_LESSON21_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4
#define RGB_LED_R_PIN                       GPIO_NUM_32
#define RGB_LED_G_PIN                       GPIO_NUM_23
#define RGB_LED_B_PIN                       GPIO_NUM_33


#endif //_BOARD_CONFIG_H

#endif