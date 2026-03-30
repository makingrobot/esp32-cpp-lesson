#include "config.h"
#if BOARD_LESSON72 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

/*****
 * 本文件主要用于配置硬件相关的设置，如引脚
 */

#define BUILTIN_LED_PIN                     GPIO_NUM_4

// OLED
#define I2C_SCL_PIN                         GPIO_NUM_22  //  
#define I2C_SDA_PIN                         GPIO_NUM_21  //  
#define OLED_I2C_ADDRESS                    0x3D
#define DISPLAY_WIDTH                       128
#define DISPLAY_HEIGHT                      64


#endif //_BOARD_CONFIG_H

#endif