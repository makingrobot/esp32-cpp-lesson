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
    while (1) {
        _this->Task1Loop();
    }
}

void ExampleApp::OnInit() {
    queue_ = xQueueCreate(10, sizeof(uint32_t));

    xTaskCreate(_task1_func, "Task1", 4096, this, 1, &task1_handle_);
}

void ExampleApp::OnLoop() {

    uint32_t value = 1;
    if (xQueueSend(queue_, &value, 0) != pdPASS) {
        Log::Warn(TAG, "发送数据到队列失败。");
    }

    delay(100);
}

void ExampleApp::Task1Loop() {

    uint32_t receive = 0;
    if (xQueueReceive(queue_, &receive, portMAX_DELAY) != pdPASS) {
        Log::Warn(TAG, "从队列接收数据失败。");
    }

    delay(100);
}

#endif 