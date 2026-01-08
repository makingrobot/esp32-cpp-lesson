/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit2-Lesson22：Ws2812灯条
 */
#include "config.h"
#if APP_LESSON22_B==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit2 lesson22 application.")

#include <string>
#include "src/framework/app/application.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    const std::string& GetAppName() const override { return "Unit2-Lesson22"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:

};

#endif //_MY_APPLICATION_H

#endif 