/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _SERVO_DRIVER_H
#define _SERVO_DRIVER_H

#include <Arduino.h>
#include <Servo.h>
#include "actuator.h"

#define TAG "SG90Driver"

/**
 * SG90舵机驱动
 */
class SG90Driver : public Actuator {
public:
    SG90Driver(gpio_num_t pin) 
            : servo_pin_(pin) { 

        pinMode(servo_pin_, OUTPUT);
    }

    virtual ~SG90Driver() { 
        
    };



private:
    const gpio_num_t servo_pin_;


};

#endif //_SERVO_DRIVER_H