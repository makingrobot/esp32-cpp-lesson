/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson64：资源互斥访问
 */
#include "config.h"
#if APP_LESSON64_A==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit6 lesson62 application.")

#include <string>
#include "src/framework/app/application.h"
#include "src/framework/sys/frt_task.h"
#include "src/framework/sys/mutex.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    void Task1Loop();
    void Task2Loop();
    void AccessResource(const std::string& tag);

    const std::string& GetAppName() const override { return "Unit6-Lesson62"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    FrtTask *task1_;
    FrtTask *task2_;
    
    Mutex *mutex_;
    volatile uint32_t count_ = 0;
    
};

#endif //_MY_APPLICATION_H

#endif 