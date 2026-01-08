/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson22：Ws2812灯条
 */
#include "config.h"
#if APP_LESSON22_A==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/led/led.h"
#include "src/framework/led/ws2812_led.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    //Ws2812Led* ws_led = (Ws2812Led *)Board::GetInstance().GetLed();
    //std::vector<uint8_t> light_set = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //ws_led->SetLightNo(light_set);
}

void MyApplication::OnLoop() {
    Led *led = Board::GetInstance().GetLed();
    led->TurnOn();
    delay(1000);
    led->TurnOff();
    delay(1000);
}

#endif 