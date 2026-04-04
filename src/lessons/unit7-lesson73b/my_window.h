/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit7-Lesson73：TFT-LCD显示屏
 */
#include "config.h"
#if APP_LESSON73_B == 1

#ifndef _MY_WINDOW_H
#define _MY_WINDOW_H

#include <TFT_eSPI.h>
#include <string>
#include "src/framework/display/tft_window.h"

class MyWindow : public TftWindow {
public:
    MyWindow();

    void SetStatus(const std::string& status) override { }
    void SetText(uint8_t line, const std::string& text) override { }
   
    void Update();
    
};

#endif //_My_WINDOW_H

#endif