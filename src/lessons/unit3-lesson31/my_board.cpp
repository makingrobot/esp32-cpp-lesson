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
#include "src/framework/board/onebutton_impl.h"

#define TAG "MyBoard"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    std::shared_ptr<Button> button1 = std::make_shared<OneButtonImpl>(kManualButton, MANUAL_BUTTON_PIN, false);
    button1->BindAction(ButtonAction::Click);
    button1->BindAction(ButtonAction::DoubleClick);
    AddButton(button1);

    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::ButtonTick() {
    for (const auto& pair : button_map()) {
        pair.second->Tick();
    }
}

#endif 