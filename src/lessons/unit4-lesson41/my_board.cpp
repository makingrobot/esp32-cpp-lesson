/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if BOARD_LESSON41 == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    // 步骤一：创建传感器对象
    std::shared_ptr<DigitalSensor> sensor_ptr = std::make_shared<DigitalSensor>(TOUCH_2_PIN);
    sensor_ptr->OnNewData([](const SensorValue& value){
        auto& app = Application::GetInstance();
        app.OnSensorDataEvent(kTouch2, value);
    });
    AddSensor(kTouch2, sensor_ptr);

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 