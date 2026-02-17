/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson61b：定时器
 */
#include "config.h"
#if APP_LESSON61_B==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/sys/timer.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    timer1_ = TimerFactory::CreateTimer("timer1");
    timer1_->Start(1000, [this]() {
        Timer1Task();
    });

    timer2_ = TimerFactory::CreateTimer("timer2");
    timer2_->Start(500, [this]() {
        Timer2Task();
    });
}

void MyApplication::OnLoop() {

    delay(1);
}

void MyApplication::Timer1Task() {
    Log::Info(TAG, "Time1Task execute.");

    Led *led = Board::GetInstance().GetLed();
    if (state_==0) {
        led->TurnOn();
        state_ = 1;
    } else {
        led->TurnOff();
        state_ = 0;
    }
}

void MyApplication::Timer2Task() {
    Log::Info(TAG, "Time2Task execute...");
    
    // 执行时间大于定时器时间(500s)
    delay(800);
}

#endif 