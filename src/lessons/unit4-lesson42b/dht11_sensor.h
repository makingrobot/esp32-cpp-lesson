/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson42b：温湿度传感器
 */
#include "config.h"
#if APP_LESSON42_B==1

#ifndef _DHT11_SENSOR_H
#define _DHT11_SENSOR_H

#include <string>
#include <Arduino.h>
#include <DHT.h> //https://github.com/adafruit/DHT-sensor-library
#include "src/framework/peripheral/sensor.h"
#include "src/framework/peripheral/sensor_value.h"

class DhtSensorValue : public SensorValue {
public:
    void SetValue(float wendu, float shidu) {
        wendu_ = wendu;
        shidu_ = shidu;
    }

    const float wendu() const { return wendu_; }
    const float shidu() const { return shidu_; }

private:
    float wendu_;
    float shidu_;
};

class Dht11Sensor : public Sensor {
public:
    Dht11Sensor(const std::string& name, gpio_num_t pin) : Sensor(name) {
        dht_ = new DHT(pin, DHT11);
        dht_->begin();
    }

protected:
    void InitValue() override {
        sensor_val_ = new DhtSensorValue();
    }

    bool ReadValue() override {
        float shidu = dht_->readHumidity();
        float wendu = dht_->readTemperature();

        ((DhtSensorValue*)sensor_val_)->SetValue(wendu, shidu);
        return true;
    }

private:
    DHT* dht_;
    
};

#endif //_DHT11_SENSOR_H

#endif