#include "config.h"
#if BOARD_XPSTEM_IOT_DEVKIT_SUIT == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#define BOOT_BUTTON_PIN             GPIO_NUM_0  // Button

#define BUILTIN_LED_PIN             GPIO_NUM_4

#define I2C_SCL_PIN                 GPIO_NUM_22  //  
#define I2C_SDA_PIN                 GPIO_NUM_21  //  

// LCD模块 ST7796
#define DISPLAY_LED_PIN             GPIO_NUM_12
#define DISPLAY_SCK_PIN             GPIO_NUM_13
#define DISPLAY_MOSI_PIN            GPIO_NUM_14
#define DISPLAY_DC_PIN              GPIO_NUM_15
#define DISPLAY_RST_PIN             GPIO_NUM_16
#define DISPLAY_CS_PIN              GPIO_NUM_17
#define DISPLAY_MISO_PIN            GPIO_NUM_NC

#define DISPLAY_WIDTH               320
#define DISPLAY_HEIGHT              240
#define DISPLAY_MIRROR_X            true
#define DISPLAY_MIRROR_Y            false
#define DISPLAY_SWAP_XY             false
#define DISPLAY_INVERT_COLOR        true
#define DISPLAY_RGB_ORDER           LCD_RGB_ELEMENT_ORDER_BGR
#define DISPLAY_OFFSET_X            0
#define DISPLAY_OFFSET_Y            0
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT false
#define DISPLAY_SPI_MODE            0

#endif //_BOARD_CONFIG_H

#endif