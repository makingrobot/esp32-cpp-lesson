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
#if APP_LESSON32_A==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    // do your init.
}

void MyApplication::OnLoop() {

    if (touch1_detected_) {
        Led *led = Board::GetInstance().GetLed();
        led->TurnOn();
        delay(200);
        led->TurnOff();
        touch1_detected_ = false;
    }

    delay(1);
}

bool MyApplication::OnPinTouchEvent(const std::string& pin_name) {
    if (pin_name == kTouch1) {
        touch1_detected_=true;
        return true;
    }

    return Application::OnPinTouchEvent(pin_name);
}

#endif 