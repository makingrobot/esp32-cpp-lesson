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
#if BOARD_LESSON21_A == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/rgb_led.h"

#define TAG "MyBoard"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new RgbLed(RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, false); 

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 