/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#ifdef APP_LESSON12==1

#include <Arduino.h>
#include <string>
#include "animal.h"
#include "dog.h"
#include "cat.h"

void feed(Animal *animal) {
    animal->Feed("骨头");
    //animal->Feed("鱼");
    animal->Shout();
}

void setup() {
    Serial.begin(115200);
    Serial.println("application starting.");

    Dog *dog1 = new Dog("来福");
    feed(dog1);

    Cat *cat1 = new Cat("旺财");
    feed(cat1);

    delete dog1;
    delete cat1;
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