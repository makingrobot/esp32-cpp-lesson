#include "config.h"
#if APP_LESSON81 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define DISPLAY_WIDTH                       240
#define DISPLAY_HEIGHT                      320


#endif //_BOARD_CONFIG_H

#endif