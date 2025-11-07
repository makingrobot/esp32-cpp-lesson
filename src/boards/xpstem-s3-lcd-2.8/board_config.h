#include "config.h"
#if BOARD_XPSTEM_S3_LCD_2_80 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

#include <driver/gpio.h>

// I2c
#define I2C_SDA_PIN                 GPIO_NUM_16
#define I2C_SCL_PIN                 GPIO_NUM_15

// ES8311
#define AUDIO_CODEC_PA_PIN          GPIO_NUM_1
#define AUDIO_CODEC_ES8311_ADDR     ES8311_CODEC_DEFAULT_ADDR

#define AUDIO_I2S_MCLK_PIN              GPIO_NUM_4
#define AUDIO_I2S_BCLK_PIN              GPIO_NUM_5
#define AUDIO_I2S_DOUT_PIN              GPIO_NUM_8
#define AUDIO_I2S_WS_PIN                GPIO_NUM_7
#define AUDIO_I2S_DIN_PIN               GPIO_NUM_6

#define AUDIO_INPUT_SAMPLE_RATE     16000
#define AUDIO_OUTPUT_SAMPLE_RATE    16000

// Button
#define BOOT_BUTTON_PIN             GPIO_NUM_0

// Led
#define BUILTIN_LED_PIN             GPIO_NUM_42

// SPI LCD ILI9341
#define DISPLAY_MOSI_PIN            GPIO_NUM_11
#define DISPLAY_CLK_PIN             GPIO_NUM_12
#define DISPLAY_BACKLIGHT_PIN       GPIO_NUM_45
#define DISPLAY_DC_PIN              GPIO_NUM_46
#define DISPLAY_CS_PIN              GPIO_NUM_10
#define DISPLAY_RST_PIN             GPIO_NUM_NC

// Touch FT6336
#define TOUCH_RST_PIN               GPIO_NUM_18
#define TOUCH_INT_PIN               GPIO_NUM_17
#define TOUCH_FT6336_ADDR           0x38

// Battery ADC
#define BATTERY_ADC_PIN               GPIO_NUM_9
#define BATTERY_ADC_UNIT              ADC_UNIT_1
#define BATTERY_ADC_CHANNEL           ADC_CHANNEL_8

// SD MMC
#define SD_MMC_CLK                  38
#define SD_MMC_CMD                  40
#define SD_MMC_D1                   39
#define SD_MMC_D2                   41
#define SD_MMC_D3                   48
#define SD_MMC_D4                   47

#define DISPLAY_WIDTH               240
#define DISPLAY_HEIGHT              320
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