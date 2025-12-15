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

#ifndef _EXAMPLE_APP_H
#define _EXAMPLE_APP_H

#pragma message("Compile unit6 lesson63a application.")

#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "src/framework/app/application.h"

class ExampleApp : public Application {
public:
    ExampleApp();
    
    void Task1Loop();

    const std::string& GetAppName() const override { return "Unit6-Lesson63a"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    QueueHandle_t queue_;
    TaskHandle_t task1_handle_;

};

#endif //_EXAMPLE_APP_H

#endif 