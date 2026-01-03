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

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit6 lesson62b application.")

#include <string>
#include <freertos/FreeRTOS.h>
#include "src/framework/app/application.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    void Task1Loop();
    void Task2Loop();

    const std::string& GetAppName() const override { return "Unit6-Lesson62b"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    int state_ = 0;
    TaskHandle_t task1_handle_;
    TaskHandle_t task2_handle_;
    
};

#endif //_MY_APPLICATION_H

#endif 