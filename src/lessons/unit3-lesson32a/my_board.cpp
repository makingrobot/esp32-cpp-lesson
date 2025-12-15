/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit3-Lesson32：触摸输入
 */
#include "config.h"
#if BOARD_LESSON32_A == 1

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

    xTaskCreate([](void* pvParam){
        while (1) {
            touch_value_t tv = touchRead(TOUCH_1_PIN);
            if (tv < 1000) {
                Log::Info(TAG, "Touch detected.");

                Application& app = Application::GetInstance();
                app.OnPinTouchEvent(kTouch1);
            }

            delay(100);
        }
    }, "TouchDetected_Task", 4096, NULL, 1, NULL);

    Log::Info( TAG, "===== Board config completed. =====");
}

#endif 