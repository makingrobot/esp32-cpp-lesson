/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson83：在网页上控制设备
 */
#include "config.h"
#if BOARD_LESSON83 == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>

#include "src/framework/board/wifi_board.h"
#include "src/framework/led/led.h"

class MyBoard : public WifiBoard {
private:
    Led* led_ = nullptr;
    Display *display_ = nullptr;

    void InitDisplay();

public:
    MyBoard();
    Led* GetLed() override { return led_; }
    Display* GetDisplay() override { return display_; }

};

#endif //_MY_BOARD_H

#endif 