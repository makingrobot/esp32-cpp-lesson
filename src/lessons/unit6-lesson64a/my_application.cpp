/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson64：资源互斥访问
 */
#include "config.h"
#if APP_LESSON64_A==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/sys/mutex/frt_mutex.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    mutex_ = new FrtMutex(); // 创建FreeRTOS互斥对象

    task1_ = new FrtTask(std::string("task1"));
    task1_->OnLoop([this](){
        Task1Loop();
    });
    task1_->Start(4096, tskIDLE_PRIORITY+1);

    task2_ = new FrtTask(std::string("Task2"));
    task2_->OnLoop([this](){
        Task2Loop();
    });
    task2_->Start(4096, tskIDLE_PRIORITY+1);
}

void MyApplication::OnLoop() {
    delay(1);
}

void MyApplication::Task1Loop() {
    AccessResource("task1");
    delay(200);
}

void MyApplication::Task2Loop() {
    AccessResource("task2");
    delay(300);
}

void MyApplication::AccessResource(const std::string& owner) {
    MutexGuard guard(mutex_, 0);
    if (guard.IsLocked())
    {
        // 独占访问代码
        Led *led = Board::GetInstance().GetLed();
        led->TurnOn();
        delay(500);
        led->TurnOff();
        delay(500);

        count_++;
        Log::Info(TAG, "call by %s, count: %d", owner.c_str(), count_);
    }
}

#endif 