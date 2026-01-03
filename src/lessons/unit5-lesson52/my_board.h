/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit5-Lesson51：舵机控制
 */
#include "config.h"
#if BOARD_LESSON52 == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>

#include "src/framework/board/board.h"
#include "src/framework/led/led.h"
#include "src/framework/board/button.h"

static const std::string kManualButton = "manual_button";
static const std::string kDht11 = "dht11";
static const std::string kIrSensor = "ir_sensor";
static const std::string kRelay = "relay";
static const std::string kSG90 = "sg90";

class MyBoard : public Board {
private:
    Led* led_ = nullptr;
    Button *manual_button_ = nullptr;

public:
    MyBoard();
    Led* GetLed() override { return led_; }

    void ButtonTick();
};

#endif //_MY_BOARD_H

#endif 