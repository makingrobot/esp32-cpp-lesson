/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson22：Ws2812灯条
 */
#include "config.h"
#if BOARD_LESSON22_B == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/ws2812_led.h"

#define TAG "MyBoard"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new Ws2812Led(WS2812_PIN, 10); // no pwm

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 