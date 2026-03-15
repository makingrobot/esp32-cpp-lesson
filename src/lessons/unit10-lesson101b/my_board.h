/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson101：音频输出
 */
#include "config.h"
#if BOARD_LESSON101_B == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>

#include "src/framework/board/wifi_board.h"
#include "src/framework/led/led.h"
#include "src/framework/file/file_system.h"
#include "src/framework/audio/audio_codec.h"

class MyBoard : public WifiBoard {
private:
    Led *led_ = nullptr;
    FileSystem *filesystem_ = nullptr;
    AudioCodec *audio_codec_ = nullptr;

    void InitFileSystem();
    void InitAudioCodec();
    
public:
    MyBoard();
    Led* GetLed() override { return led_; }
    FileSystem* GetFileSystem() override { return filesystem_; }
    AudioCodec* GetAudioCodec() override { return audio_codec_; }

};

#endif //_MY_BOARD_H

#endif 