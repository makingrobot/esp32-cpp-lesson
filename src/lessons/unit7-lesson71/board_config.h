#include "config.h"
#if APP_LESSON71 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

#define I2C_SDA_PIN                         GPIO_NUM_NC
#define I2C_SCL_PIN                         GPIO_NUM_NC


#endif //_BOARD_CONFIG_H

#endif