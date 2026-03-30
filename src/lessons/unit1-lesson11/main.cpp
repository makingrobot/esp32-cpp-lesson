/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#ifdef APP_LESSON11==1

#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("application starting.");
}

void loop() {
    
}

void* create_board() {
    return nullptr;
}

void* create_application() {
    return nullptr;
}

#endif