/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson83：在网页上控制设备
 */
#include "config.h"
#if APP_LESSON83==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit8 lesson83 application.")

#include <string>
#include <Arduino.h>
#include <WebServer.h>
#include "src/framework/app/application.h"
#include "src/framework/sys/task.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    const std::string& GetAppName() const override { return "Unit8-Lesson83"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    void StartWebServer();
    
    WebServer *webserver_;
    Task *webtask_;
};

#endif //_MY_APPLICATION_H

#endif 