/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson23：Ws2812灯条
 */
#include "config.h"
#if APP_LESSON22==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/led/led.h"
#include "src/framework/led/ws2812_led.h"

#define TAG "ExampleApp"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    // Ws2812Led* ws_led = (Ws2812Led *)Board::GetInstance().GetLed();
    // ws_led->SetColor(50, 0, 0);
    // ws_led->Blink(-1, 1000);

}

void MyApplication::OnLoop() {
    Ws2812Led* ws_led = (Ws2812Led *)Board::GetInstance().GetLed();

    std::vector<uint8_t> nums = {0, 1, 2};
    ws_led->SetColor(0, 50, 0);
    ws_led->TurnOn(nums);
    delay(1000);

    nums = {3, 4, 5};
    ws_led->SetColor(0, 50, 50);
    ws_led->TurnOn(nums);
    delay(1000);

    ws_led->TurnOff();
    delay(1000);
}

#endif 