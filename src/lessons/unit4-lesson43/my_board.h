/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson42：温湿度传感器
 */
#include "config.h"
#if BOARD_LESSON43 == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include "src/framework/board/board.h"
#include "src/framework/led/led.h"

static const std::string kTouch1 = "touch1";
static const std::string kTouch2 = "touch2";
static const std::string kDht11 = "dht11";

class MyBoard : public Board {
private:
    Led* led_ = nullptr;

public:
    MyBoard();
    Led* GetLed() override { return led_; }

};

#endif //_MY_BOARD_H

#endif 