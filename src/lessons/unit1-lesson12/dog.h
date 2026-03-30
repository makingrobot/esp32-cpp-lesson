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
#ifdef APP_LESSON12==1

#ifndef _DOG_H
#define _DOG_H

class Dog : public Animal {
public:
    Dog(const std::string& nickname) : Animal(nickname) { }

    bool Feed(const std::string& food) override {
        if (food == "骨头") {
            Serial.printf("%s：吃了一根骨头\n", nickname_.c_str());
            return true;
        }

        Serial.printf("%s：狗要吃骨头\n", nickname_.c_str());
        return false;
    }

    void Shout() override {
        Serial.printf("%s：汪~汪~汪~\n", nickname_.c_str());
    }

    // 看门
    void WatchDoor() {

    }
};

#endif

#endif