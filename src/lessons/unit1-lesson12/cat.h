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

#ifndef _CAT_H
#define _CAT_H

class Cat : public Animal {
public:
    Cat(const std::string& nickname) : Animal(nickname) { }

    bool Feed(const std::string& food) override {
        if (food == "鱼") {
            Serial.printf("%s：吃了一条鱼\n", nickname_.c_str());
            return true;
        }

        Serial.printf("%s：猫要吃鱼\n", nickname_.c_str());
        return false;
    }

    void Shout() override {
        Serial.printf("%S：喵~喵~喵~\n", nickname_.c_str());
    }

    // 抓鱼
    void CatchFish() {

    }
};

#endif

#endif