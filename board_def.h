/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _BOARD_DEF_H
#define _BOARD_DEF_H

#include "config.h"

#if BOARD_XPSTEM_S3_LCD_2_80 == 1
#define BOARD_NAME "xpstem-s3-lcd-2.80"
#include "src/boards/xpstem-s3-lcd-2.8/xpstem-s3-lcd-2.8.h"
#endif //BOARD_XPSTEM_S3_LCD_2_80


#if BOARD_XPSTEM_IOT_DEVKIT_SUIT == 1
#define BOARD_NAME "xpstem-iot-devkit-suit"
#include "src/boards/xpstem-iot-devkit-suit/xpstem-iot-devkit-suit.h"
#endif //BOARD_XPSTEM_IOT_DEVKIT_SUIT


#if BOARD_XPSTEM_IOT_WATERING_SUIT == 1
#define BOARD_NAME "xpstem-iot-watering-suit"
#include "src/boards/xpstem-iot-watering-suit/xpstem-iot-watering-suit.h"
#endif //BOARD_XPSTEM_IOT_WATERING_SUIT


#if BOARD_XPSTEM_S3_ELECTRONIC_SUIT == 1
#define BOARD_NAME "xpstem-s3-electronic-suit"
#include "src/boards/xpstem-s3-electronic-suit/xpstem-s3-electronic-suit.h"
#endif //BOARD_XPSTEM_S3_ELECTRONIC_SUIT


#if BOARD_XINGZHI_MATRIXBIT_V3 == 1
#define BOARD_NAME "xingzhi-matrixbit-v3"
#include "src/boards/xingzhi-matrixbit-v3/xingzhi-matrixbit-v3.h"
#endif //BOARD_XINGZHI_MATRIXBIT_V3


#endif //_BOARD_DEF_H