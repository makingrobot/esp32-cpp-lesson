#include "config.h"
#if APP_LESSON92 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define DISPLAY_WIDTH                       240
#define DISPLAY_HEIGHT                      320

#define SD_MOSI_PIN                         GPIO_NUM_17
#define SD_MISO_PIN                         GPIO_NUM_16
#define SD_CLK_PIN                          GPIO_NUM_15
#define SD_CS_PIN                           GPIO_NUM_14


#endif //_BOARD_CONFIG_H

#endif