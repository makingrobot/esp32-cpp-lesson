
#include "analog_sensor.h"
#include <Arduino.h>
#include <esp_log.h>

#define TAG "AnalogSensor"

AnalogSensor::AnalogSensor(gpio_num_t sensor_pin) : sensor_pin_(sensor_pin) {

    sensor_ticker_ = new Ticker();
}

AnalogSensor::~AnalogSensor() {
    if (sensor_ticker_ != nullptr) {
        sensor_ticker_->detach();
        sensor_ticker_ = nullptr;
    }
}

void TickerCallback(AnalogSensor *arg) {
    arg->ReadData();
}

void AnalogSensor::Start(uint32_t interval) {
    if (sensor_ticker_ != nullptr) {
        sensor_ticker_->detach();
    }
    
    sensor_ticker_->attach(1, TickerCallback, this);
    ESP_LOGI(TAG, "sensor timer started.");
}

void AnalogSensor::Stop() {
    if (sensor_ticker_ != nullptr) {
        sensor_ticker_->detach();
    }
}

void AnalogSensor::ReadData() {
    int count = 3;
    int total_val = 0;
    for (int i=0; i<count; i++) {
        total_val += analogRead(sensor_pin_);
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms
    }

    // 取均值
    sensor_val_ = total_val / count;

    if (on_newdata_callback_) {
        on_newdata_callback_(sensor_val_);
    }
}