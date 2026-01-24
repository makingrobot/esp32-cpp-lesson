/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson43：旋转电位器
 */
#include "config.h"
#if BOARD_LESSON42_A == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/rgb_led.h"
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"

#define TAG "MyBoard"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new RgbLed(RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, false); 

    Log::Info(TAG, "initial sensor.");
    std::shared_ptr<AnalogSensor> sensor_ptr = std::make_shared<AnalogSensor>(kPotentiometer, POTENTIOMETER_PIN);
    AddSensor(sensor_ptr);

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 