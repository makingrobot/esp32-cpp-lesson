/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson101：音频输出
 */
#include "config.h"
#if APP_LESSON101_B==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#pragma message("Compile unit10 lesson101 application.")

#include <string>
#include <Arduino.h>
#include "src/framework/app/application.h"
#include "src/framework/audio/audio_pipe.h"

class MyApplication : public Application {
public:
    MyApplication();
    
    const std::string& GetAppName() const override { return PSTR("Unit10-Lesson101"); }
    const std::string& GetAppVersion() const override { return PSTR("1.0.0"); }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    AudioPipe *pipe_;
};

#endif //_MY_APPLICATION_H

#endif 