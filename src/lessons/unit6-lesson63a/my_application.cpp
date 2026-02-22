/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson63：多线程和同步
 */
#include "config.h"
#if APP_LESSON63_A==1

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
    queue_ = xQueueCreate(10, sizeof(int));

    task1_ = new Task("Task1");
    task1_->OnLoop([this](){
        Task1Loop();
    });
    task1_->Start( 4096, tskIDLE_PRIORITY+1);
    
    task2_ = new Task("Task2");
    task2_->OnLoop([this](){
        Task2Loop();
    });
    task2_->Start( 4096, tskIDLE_PRIORITY+1);
}

void MyApplication::OnLoop() {
    delay(1);
}

void MyApplication::Task1Loop() {
    state_ = (state_==0 ? 1 : 0);

    if (xQueueSend(queue_, &state_, 0) != pdPASS) {
        Log::Warn(TAG, "发送数据到队列失败。");
    }

    delay(500);
}

void MyApplication::Task2Loop() {
    int receive = 0;
    if (xQueueReceive(queue_, &receive, portMAX_DELAY) != pdPASS) {
        Log::Warn(TAG, "从队列接收数据失败。");
        return;
    }

    Led *led = Board::GetInstance().GetLed();
    if (receive==1) 
    {
        led->TurnOn();
    }
    else 
    {
        led->TurnOff();
    }
}

#endif 