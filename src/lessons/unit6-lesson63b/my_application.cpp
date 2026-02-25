/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson63：FreeRTOS任务间通信
 */
#include "config.h"
#if APP_LESSON63_B==1

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
    event_group_ = xEventGroupCreate();

    // 任务一
    task1_ = new Task("Task1");
    task1_->OnLoop([this](){
        // 一些处理
        delay(500);
        xEventGroupSetBits(event_group_, 0b00000001);
    });
    task1_->Start(4096, tskIDLE_PRIORITY+1);

    // 任务二
    task2_ = new Task("Task2");
    task2_->OnLoop([this](){
        // 一些处理
        delay(1000);
        xEventGroupSetBits(event_group_, 0b00000010);
    });
    task2_->Start(4096, tskIDLE_PRIORITY+1);
}

void MyApplication::OnLoop() {
    // 等待全部事件位被设置（事件位AND）
    auto bits = xEventGroupWaitBits(event_group_, 
        0b00000011,
        pdTRUE, /* 自动清除，避免重复响应 */
        pdTRUE, /* 所有事件位被设置就返回 */
        portMAX_DELAY /* 无限期等待，也可使用pdMS_TO_TICKS指定等待时长 */
    );

    Led *led = Board::GetInstance().GetLed();
    led->TurnOn();
    
    // 有事件设置就触发（事件位OR）
    /*
    auto bits = xEventGroupWaitBits(event_group_, 
        0b00000011,
        pdTRUE, // 自动清除，避免重复响应 
        pdFALSE, // 所有事件位被设置就返回 
        portMAX_DELAY // 无限期等待，也可使用pdMS_TO_TICKS指定等待时长 
    );

    if (bits & 0b01 = 0b01) {
        Led *led = Board::GetInstance().GetLed();
        led->TurnOn();
    } else (bits & 0b10 = 0b10) {
        
    }
    */

    delay(1);
}

#endif 