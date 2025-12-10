/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson23：点亮LED
 */
#include "config.h"
#if APP_LESSON21==1

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"

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

    Led *led = Board::GetInstance().GetLed();
    led->TurnOn();
    delay(1000);
    led->TurnOff();
    delay(1000);
}

#endif 