/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson42：温湿度传感器
 */
#include "config.h"
#if BOARD_LESSON42==1

#ifndef _DHT11_SENSOR_H
#define _DHT11_SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include <vector>

#include "src/framework/peripheral/sensor.h"

class Dht11Sensor : public Sensor {
public:
    Dht11Sensor(gpio_num_t pin) : Sensor() {
        dht_ = new DHT(pin, DHT11);
        dht_->begin();
    }

    void ReadValue(SensorValue *value) override {
        float shidu = dht_->readHumidity();
        float wendu = dht_->readTemperature();

        std::vector<float> list;
        list.push_back(wendu);
        list.push_back(shidu);

        value->setFloatList(list);
        return true;
    }

private:
    DHT* dht_;
    
};

#endif //_DHT11_SENSOR_H

#endif