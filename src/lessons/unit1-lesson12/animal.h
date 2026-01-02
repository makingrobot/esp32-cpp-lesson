/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
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