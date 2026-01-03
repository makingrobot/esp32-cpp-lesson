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

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit6 lesson63b application.")

#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "src/framework/app/application.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    const std::string& GetAppName() const override { return "Unit6-Lesson63b"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

    EventGroupHandle_t event_group() const { return event_group_; }
    
protected:
    void OnInit() override;
    void OnLoop() override;

private:
    EventGroupHandle_t event_group_;

};

#endif //_MY_APPLICATION_H

#endif 