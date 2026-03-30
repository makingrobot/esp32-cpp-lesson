/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit9-Lesson92：文件系统应用
 */
#include "config.h"
#if APP_LESSON92==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit9 lesson92 application.")

#include <string>
#include <Arduino.h>
#include <WebServer.h>
#include <FS.h>
#include "src/framework/app/application.h"
#include "src/framework/sys/frt_task.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    const std::string& GetAppName() const override { return "Unit9-Lesson92"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    void StartWebServer();

    void OutputFile(String path);
    void HandleFileUpload();
    void HandleNotFound();

    WebServer *webserver_;
    FrtTask *webtask_;
    FrtFile uploadfile_;
};

#endif //_MY_APPLICATION_H

#endif 