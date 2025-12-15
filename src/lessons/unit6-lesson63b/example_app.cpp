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
#if APP_LESSON63_B==1

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new ExampleApp();
}

ExampleApp::ExampleApp() : Application() { 

}

void _task1_func(void* pvParam) {
    
    ExampleApp *_this = (ExampleApp*)pvParam;


    xEventGroupSetBits(_this->event_group(), 0b00000001);
    vTaskDelete(NULL);
}

void _task2_func(void* pvParam) {
    
    ExampleApp *_this = (ExampleApp*)pvParam;

    
    xEventGroupSetBits(_this->event_group(), 0b00000010);
    vTaskDelete(NULL);
}

void ExampleApp::OnInit() {
    
    event_group_ = xEventGroupCreate();

    xTaskCreate(_task1_func, "Task1", 4096, this, 1, NULL);
    xTaskCreate(_task2_func, "Task2", 4096, this, 1, NULL);

}

void ExampleApp::OnLoop() {

    // 等待事件位被设置
    auto bits = xEventGroupWaitBits(event_group_, 
        0b00000011,
        pdTRUE, /* 自动清除，避免重复响应 */
        pdTRUE, /* 所有事件位被设置就返回 */
        portMAX_DELAY /* 无限期等待，也可使用pdMS_TO_TICKS指定等待时长 */
    );




    delay(1);
}

#endif 