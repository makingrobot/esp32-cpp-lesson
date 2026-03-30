#include "board_def.h"
#if BOARD_LESSON102_A == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define SD_CLK_PIN                          GPIO_NUM_3
#define SD_MOSI_PIN                         GPIO_NUM_4
#define SD_MISO_PIN                         GPIO_NUM_5
#define SD_CS_PIN                           GPIO_NUM_2

#define MIC_BCLK_PIN                        GPIO_NUM_17
#define MIC_WS_PIN                          GPIO_NUM_18
#define MIC_DIN_PIN                         GPIO_NUM_48


#endif //_BOARD_CONFIG_H

#endif