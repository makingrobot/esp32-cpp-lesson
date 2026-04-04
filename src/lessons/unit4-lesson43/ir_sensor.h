/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习和教学，商业用途请联系作者。
 * 本程序不对用户因使用程序而造成任何形式的损失负责。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson43：红外遥控
 */
#include "config.h"
#if APP_LESSON43==1

#ifndef _IR_SENSOR_H
#define _IR_SENSOR_H

#include <Arduino.h>
#include <IRremote.h>

#include "src/framework/peripheral/sensor.h"

class IrSensor : public Sensor {
public:
    IrSensor(const std::string& name, gpio_num_t pin) : Sensor(name) {
        ir_recv_ = new IRrecv(pin);
        ir_recv_->enableIRIn();
    }

    bool ReadValue() override {
        
        if (ir_recv_->decode()) {
            struct IRData *pIrData = &ir_recv_->decodedIRData;
            sensor_val_->SetUlongValue(pIrData->decodedRawData);

            ir_recv_->resume();

            // 不等于0的码为有效码，返回true。
            if (sensor_val_->ulongValue() != 0) {
                return true;
            }
        }

        return false;
    }

private:
    IRrecv *ir_recv_ = nullptr;
};

#endif //_IR_SENSOR_H

#endif