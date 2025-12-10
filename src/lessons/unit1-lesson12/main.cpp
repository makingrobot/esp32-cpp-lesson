/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#ifdef APP_LESSON12==1

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