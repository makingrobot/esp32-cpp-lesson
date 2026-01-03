/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson21：三色LED
 */
#include "config.h"
#if APP_LESSON21_B==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"

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

    Led *led = Board::GetInstance().GetLed();

    led->SetColor(255, 0, 0);
    led->TurnOn();
    delay(2000);

    // 过滤
    for (int i=0; i<=250; i+=50) {
        led->SetColor(255-i, i, 0);
        led->TurnOn();
        delay(200);
    }

    led->SetColor(0, 255, 0);
    led->TurnOn();
    delay(2000);

    // 过滤
    for (int i=0; i<=250; i+=50) {
        led->SetColor(0, 255-i, i);
        led->TurnOn();
        delay(200);
    }

    led->SetColor(0, 0, 255);
    led->TurnOn();
    delay(2000);

    // 过滤
    for (int i=0; i<=250; i+=50) {
        led->SetColor(i, 0, 255-i);
        led->TurnOn();
        delay(200);
    }

}

#endif 