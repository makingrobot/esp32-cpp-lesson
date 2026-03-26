/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit7-Lesson73：TFT-LCD显示屏
 */
#include "config.h"
#if BOARD_LESSON73_B == 1

#ifndef _MY_WINDOW2_H
#define _MY_WINDOW2_H

#include <TFT_eSPI.h>
#include <string>
#include "src/framework/display/tft_window.h"

class MyWindow2 : public TftWindow {
public:
    MyWindow2();

    void SetStatus(const std::string& status) override { }
    void SetText(uint8_t line, const std::string& text) override { }
   
    void Update();
    
};

#endif //_My_WINDOW2_H

#endif