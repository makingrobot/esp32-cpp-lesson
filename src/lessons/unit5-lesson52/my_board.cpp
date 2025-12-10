/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit5-Lesson51：舵机控制
 */
#include "config.h"
#if BOARD_LESSON52 == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"
#include "l9110_driver.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    manual_button_ = new OneButton(MANUAL_BUTTON_PIN, true, false);
    manual_button_->attachClick([]() {
        Log::Info(TAG, "Manual button click.");
        Application& app = Application::GetInstance();
        app.OnPhysicalButtonEvent(kManualButton, ButtonAction::Click);
    });
    manual_button_->attachDoubleClick([]() {
        Log::Info(TAG, "Manual button doubleclick.");
        Application& app = Application::GetInstance();
        app.OnPhysicalButtonEvent(kManualButton, ButtonAction::DoubleClick);
    });

    std::shared_ptr<L9110Driver> l9110_driver_ptr = std::make_shared<L9110Driver>(L9110_A_PIN, L9110_B_PIN);
    AddActuator(kL9110, l9110_driver_ptr);
  
    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::ButtonTick() {
    manual_button_->tick();
}

#endif 