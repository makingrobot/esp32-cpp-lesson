#include "config.h"
#if BOARD_XINGZHI_MATRIXBIT_V3 == 1

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H

// 音频
#define AUDIO_INPUT_SAMPLE_RATE     24000
#define AUDIO_OUTPUT_SAMPLE_RATE    24000

#define AUDIO_INPUT_REFERENCE       true
#define AUDIO_I2S_WS_PIN            GPIO_NUM_41
#define AUDIO_I2S_MCLK_PIN          GPIO_NUM_12
#define AUDIO_I2S_BCLK_PIN          GPIO_NUM_13
#define AUDIO_I2S_DIN_PIN           GPIO_NUM_14
#define AUDIO_I2S_DOUT_PIN          GPIO_NUM_45

#define AUDIO_CODEC_PA_PIN          GPIO_NUM_21
#define AUDIO_CODEC_I2C_SDA_PIN     GPIO_NUM_1
#define AUDIO_CODEC_I2C_SCL_PIN     GPIO_NUM_2
#define AUDIO_CODEC_ES8311_ADDR     ES8311_CODEC_DEFAULT_ADDR

// 按键
#define BOOT_BUTTON_PIN             GPIO_NUM_0

// 屏幕
#define DISPLAY_MOSI_PIN            GPIO_NUM_39
#define DISPLAY_SCK_PIN             GPIO_NUM_40
#define DISPLAY_DC_PIN              GPIO_NUM_38
#define DISPLAY_CS_PIN              GPIO_NUM_NC
#define DISPLAY_RST_PIN             GPIO_NUM_NC
#define DISPLAY_BACKLIGHT_PIN       GPIO_NUM_11

#define DISPLAY_BACKLIGHT_OUTPUT_INVERT false
#define DISPLAY_INVERT_COLOR        true
#define DISPLAY_RGB_ORDER           LCD_RGB_ELEMENT_ORDER_RGB
#define DISPLAY_WIDTH               240
#define DISPLAY_HEIGHT              240
#define DISPLAY_SWAP_XY             false
#define DISPLAY_MIRROR_X            false
#define DISPLAY_MIRROR_Y            false
#define DISPLAY_OFFSET_X            0
#define DISPLAY_OFFSET_Y            0

// 4g
#define NETWORK_MODULE_POWER_IN     GPIO_NUM_NC
#define ML307_RX_PIN                GPIO_NUM_48
#define ML307_TX_PIN                GPIO_NUM_47
#define NETWORK_ZXC                 GPIO_NUM_NC

// 电源管理
#define POWER_USB_IN                GPIO_NUM_NC
#define Power_Control               GPIO_NUM_NC
#define Power_Dec                   GPIO_NUM_NC
#define POWER_CBS_ADC_UNIT          ADC_UNIT_1   // battery adc检测unit GPIO10
#define POWER_BATTERY_ADC_CHANNEL   ADC_CHANNEL_9 // 电池电量检测 GPIO10

/* Camera pins */
#define CAMERA_PIN_PWDN             -1
#define CAMERA_PIN_RESET            -1
#define CAMERA_PIN_XCLK             5
#define CAMERA_PIN_SIOD             1
#define CAMERA_PIN_SIOC             2

#define CAMERA_PIN_D7               9
#define CAMERA_PIN_D6               4
#define CAMERA_PIN_D5               6
#define CAMERA_PIN_D4               15
#define CAMERA_PIN_D3               17
#define CAMERA_PIN_D2               8
#define CAMERA_PIN_D1               18
#define CAMERA_PIN_D0               16
#define CAMERA_PIN_VSYNC            3
#define CAMERA_PIN_HREF             46
#define CAMERA_PIN_PCLK             7

#define XCLK_FREQ_HZ                24000000

#endif //_BOARD_CONFIG_H

#endif