/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _CONFIG_H
#define _CONFIG_H

//////////////////////////////////////////////////////////////////////////////////
// 应用（只能设置一个为1，其余必须为0）
#define APP_DEMO_LCD                        0   // LCD + LVGL显示DEMO
#define APP_DEMO_TFT                        1   // TFT_eSPI显示DEMO
#define APP_DEMO_U8G2                       0   // SSD1306 + U8G2 显示DEMO
#define APP_DEMO_MP3                        0   // MP3播放，需要音频外设


//////////////////////////////////////////////////////////////////////////////////
// 主板（只能设置一个为1，其余必须为0）
#define BOARD_XPSTEM_S3_LCD_2_80            0  // 小鹏AI语音机器人、ESP32-S3 2.8寸显示屏开发板
#define BOARD_XPSTEM_IOT_WATERING_SUIT      0   // 小鹏IoT浇花套件
#define BOARD_XPSTEM_IOT_DEVKIT_SUIT        0   // 小鹏IoT开发套件
#define BOARD_XPSTEM_S3_ELECTRONIC_SUIT     0   // 小鹏ESP32-S3创意电子套件
#define BOARD_XINGZHI_MATRIXBIT_V3          1   // Matrixbit V3

// 外设
#define CONFIG_USE_DISPLAY                  1   // 显示
#define CONFIG_USE_AUDIO                    1   // 音频
#define CONFIG_USE_FS                       0   // 文件系统
#define CONFIG_USE_CAMERA                   0   // 摄像头

// 图形化（只能设置一个为1，其余必须为0）
#define CONFIG_USE_LVGL                     0  // LVGL
#define CONFIG_USE_U8G2                     0   // U8G2
#define CONFIG_USE_TFT                      1   // TFT_eSPI

// 显示驱动（只能设置一个为1，其余必须为0）
#define CONFIG_USE_DISPLAY_ILI9341          0
#define CONFIG_USE_DISPLAY_ST7789           0
#define CONFIG_USE_DISPLAY_ST7796           0
#define CONFIG_USE_DISPLAY_SSD1306          0

// 音频驱动（只能设置一个为1，其余必须为0）
#define CONFIG_USE_AUDIO_ES8311             1
#define CONFIG_USE_AUDIO_ES8374             0
#define CONFIG_USE_AUDIO_ES8388             0

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

// For LVGL
#define LV_LVGL_H_INCLUDE_SIMPLE            1


//////////////////////////////////////////////////////////////////////////////////

// 特性
#define CONFIG_WIFI_CONFIGURE_ENABLE        0  // WIFI配置
#define CONFIG_CLOCK_ENABLE                 0  // 时钟（刷新界面）
#define CONFIG_OTA_ENABLE                   0  // OTA

#define CONFIG_OTA_URL                      "http://xiaozhi.xpstem.com/xiaozhi/ota/"


#endif //_CONFIG_H