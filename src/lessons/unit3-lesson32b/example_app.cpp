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
#if APP_LESSON32_B==1

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new ExampleApp();
}

ExampleApp::ExampleApp() : Application() { 

}

void ExampleApp::OnInit() {
    // do your init.
}

void ExampleApp::OnLoop() {

    if (touch1_detected_) {
        Led *led = Board::GetInstance().GetLed();
        led->TurnOn();
        delay(200);
        led->TurnOff();
        touch1_detected_ = false;
    }

    delay(1);
}

bool ExampleApp::OnPinTouchEvent(const std::string& pin_name) {
    if (pin_name == kTouch1) {
        touch1_detected_=true;
        return true;
    }

    return Application::OnPinTouchEvent(pin_name);
}

#endif 