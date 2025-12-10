/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit3-Lesson31：按键
 */
#include "config.h"
#if BOARD_LESSON31 == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    manual_button_ = new OneButton(MANUAL_BUTTON_PIN, false);
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

    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::ButtonTick() {
    manual_button_->tick();
}

#endif 