/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
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