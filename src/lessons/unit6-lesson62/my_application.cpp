/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson62：硬件定时器
 */
#include "config.h"
#if APP_LESSON62==1

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
    task1_ = new Task(std::string("task1"));
    task1_->OnLoop([this](){
        Task1Loop();
    });
    task1_->Start(4096, tskIDLE_PRIORITY+1);

    task2_ = new Task(std::string("Task2"));
    task2_->OnLoop([this](){
        Task2Loop();
    });
    task2_->Start(4096, tskIDLE_PRIORITY+1);
}

void MyApplication::OnLoop() {

    delay(1);
}

void MyApplication::Task1Loop() {
    Led *led = Board::GetInstance().GetLed();
    if (state_==0) {
        led->TurnOn();
        state_ = 1;
    } else {
        led->TurnOff();
        state_ = 0;
    }

    delay(1000);
}

void MyApplication::Task2Loop() {

    long long n = 0;
    for (int i=1; i<10000000; i++) {
        n += i;
    }
    
    Log::Info(TAG, "1...10000000 = %lld", n);

    delay(2000);
}

#endif 