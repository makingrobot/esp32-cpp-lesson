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
#if APP_LESSON63_C==1

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
    binary_semaphore_ = xSemaphoreCreateBinary();

    // 任务一
    task1_ = new Task("Task1");
    task1_->OnLoop([this](){
         /* 释放信号量 */
        xSemaphoreGive(binary_semaphore_);

        delay(2000);
    });
    task1_->Start(4096, tskIDLE_PRIORITY+1);
}

void MyApplication::OnLoop() {
    /* 等待信号量 */
    if(xSemaphoreTake(binary_semaphore_, portMAX_DELAY) == pdTRUE)
    {
        Led *led = Board::GetInstance().GetLed();
        led->TurnOn();
        delay(1000);
        led->TurnOff();
    }
    
    delay(1);
}

#endif 