/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit9-Lesson92：文件系统应用
 */
#include "config.h"
#if BOARD_LESSON92 == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>

#include "src/framework/board/wifi_board.h"
#include "src/framework/led/led.h"
#include "src/framework/file/file_system.h"

class MyBoard : public WifiBoard {
private:
    Led* led_ = nullptr;
    FileSystem* filesystem_ = nullptr;

    void InitFileSystem();
    
public:
    MyBoard();
    Led* GetLed() override { return led_; }
    FileSystem* GetFileSystem() override { return filesystem_; }

};

#endif //_MY_BOARD_H

#endif 