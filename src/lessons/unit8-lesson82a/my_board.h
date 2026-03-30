/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson82：Wifi热点与Web服务
 */
#include "config.h"
#if BOARD_LESSON82_A == 1

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