/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit5-Lesson51：继电器
 */
#include "config.h"
#if BOARD_LESSON51 == 1

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"
#include "src/framework/peripheral/switch_actuator.h"

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

    // 创建执行器件对象
    std::shared_ptr<SwitchActuator> actuator_ptr = std::make_shared<SwitchActuator>(RELAY_PIN);
    AddActuator(kRelay, actuator_ptr);

    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::ButtonTick() {
    manual_button_->tick();
}

#endif 