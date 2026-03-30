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

#ifndef _ANIMAL_H
#define _ANIMAL_H

class Animal {
public:
    Animal(const std::string& nickname) : nickname_(nickname) { }

    /**
     * 昵称
     */
    const std::string& nickname() const { return nickname_; }

    /**
     * 喂食
     */
    virtual bool Feed(const std::string& food) { return false; }
    
    /**
     * 发声
     */
    virtual void Shout() {  }

protected:
    const std::string nickname_;

private:

};

#endif //_ANIMAL_H

#endif