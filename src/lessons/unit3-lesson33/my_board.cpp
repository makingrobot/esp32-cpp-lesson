/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit3-Lesson33：触摸输入（中断方式）
 */
#include "config.h"
#if BOARD_LESSON33 == 1

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

    touchAttachInterrupt(
        TOUCH_1_PIN, 
        [](){ /* 中断调用函数 */
            Log::Info(TAG, "Touch detected.");

            Application& app = Application::GetInstance();
            app.OnPinTouchEvent(kTouch1);
        },
        1000 /* 中断触发阀值 */
    );
    //参考：https://www.xpstem.com/doc/arduino-esp32/api/touch

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 