/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _DIGITAL_EXECUTOR_H
#define _DIGITAL_EXECUTOR_H

/**
 * 数字量执行器
 */
class DigitalExecutor {
public:
    DigitalExecutor(gpio_num_t pin) : sensor_pin_(pin) { }
    virtual ~DigitalExecutor() { };

    void Output(uint8_t val) {
        current_val_ = val;
        digitalWrite(sensor_pin_, val);
    }

private:
    gpio_num_t sensor_pin_;
    uint8_t current_val_;

};

#endif //_DIGITAL_EXECUTOR_H