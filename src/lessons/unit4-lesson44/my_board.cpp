/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson44：红外遥控
 */
#include "config.h"
#if BOARD_LESSON44 == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"
#include "ir_sensor.h"

#define TAG "MyBoard"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    // 步骤一：创建传感器对象
    std::shared_ptr<IrSensor> irsensor_ptr = std::make_shared<IrSensor>(kIrSensor, IR_SENSOR_PIN);
    irsensor_ptr->BindData();
    AddSensor(irsensor_ptr);

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 