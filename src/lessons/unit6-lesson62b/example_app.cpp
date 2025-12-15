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
#if APP_LESSON62_B==1

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

void _task2_func(void *pvParam) {
    ExampleApp *_this = (ExampleApp*)pvParam;
    while (1) {
        _this->Task2Loop();
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

    xTaskCreate(
        _task2_func, 
        "Task2", 
        4096, 
        this, 
        2, 
        &task2_handle_
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

void ExampleApp::Task2Loop() {

    long long n = 0;
    for (int i=1; i<10000000; i++) {
        n += i;
    }
    
    Log::Info(TAG, "1...10000000 = %lld", n);

    delay(5000);
}

#endif 