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
#if APP_LESSON62_A==1

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

void _task1_func(void *pvParam) {
    ExampleApp *_this = (ExampleApp*)pvParam;
    while (1) {
        _this->Task1Loop();
    }
}

void ExampleApp::OnInit() {
    
    xTaskCreate(
        _task1_func, 
        "Task1", 
        4096, 
        this, 
        1, 
        &task1_handle_
    );

}

void ExampleApp::OnLoop() {

    delay(1);
}

void ExampleApp::Task1Loop() {
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

#endif 