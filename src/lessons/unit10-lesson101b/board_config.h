#include "config.h"
#if BOARD_LESSON101_B == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define SPK_BCLK_PIN                        GPIO_NUM_17
#define SPK_WS_PIN                          GPIO_NUM_18
#define SPK_DOUT_PIN                        GPIO_NUM_48


#endif //_BOARD_CONFIG_H

#endif