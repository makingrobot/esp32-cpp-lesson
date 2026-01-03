/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson21：三色LED
 */
#include "config.h"
#if BOARD_LESSON21_B == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include "src/framework/board/board.h"
#include "src/framework/led/led.h"

class MyBoard : public Board {
private:
    Led* led_ = nullptr;

public:
    MyBoard();
    Led* GetLed() override { return led_; }

};

#endif //_MY_BOARD_H

#endif 