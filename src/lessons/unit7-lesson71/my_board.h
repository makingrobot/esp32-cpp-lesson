/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson71：四段7位数码管
 */
#include "config.h"
#if BOARD_LESSON71 == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>
#include <TM1650.h>  //https://github.com/makingrobot/TM1650 patch-1分支

#include "src/framework/board/board.h"
#include "src/framework/led/led.h"

class MyBoard : public Board {
private:
    Led* led_ = nullptr;
    TM1650 *tm1650_ = nullptr;

    void InitTM1650();

public:
    MyBoard();
    Led* GetLed() override { return led_; }
    TM1650* GetTM1650() { return tm1650_; }

};

#endif //_MY_BOARD_H

#endif 