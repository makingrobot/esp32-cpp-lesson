/**
 * Iot-Devkit-Examples
 * Iot开发套件示例，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 套件详情：https://www.xpstem.com/product/iot-devkit-suit
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if BOARD_LESSON44==1

#ifndef _IR_SENSOR_H
#define _IR_SENSOR_H

#include <Arduino.h>
#include <IRremote.h>

#include "src/framework/peripheral/sensor.h"

class IrSensor : public Sensor {
public:
    IrSensor(gpio_num_t pin) : Sensor() {
        ir_recv_ = new IRrecv(pin);
        ir_recv_->enableIRIn();
    }

    bool ReadValue(SensorValue *value) override {
        
        if (ir_recv_->decode()) {
            struct IRData *pIrData = &ir_recv_->decodedIRData;
            value->setUlongValue(pIrData->decodedRawData);

            ir_recv_->resume();

            // 等于0的码视为无效码。
            if (value->ulongValue() != 0) {
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