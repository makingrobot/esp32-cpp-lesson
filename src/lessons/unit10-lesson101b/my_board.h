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
#if APP_LESSON101_B == 1

#ifndef _MY_BOARD_H
#define _MY_BOARD_H

#include <Arduino.h>

#include "src/framework/board/wifi_board.h"
#include "src/framework/led/led.h"
#include "src/framework/display/display.h"
#include "src/framework/audio/audio_codec.h"

class MyBoard : public WifiBoard {
private:
    Led *led_ = nullptr;
    Display *display_ = nullptr;
    AudioCodec *audio_codec_ = nullptr;

    void InitDisplay();
    void InitAudioCodec();
    
public:
    MyBoard();
    Led* GetLed() override { return led_; }
    Display* GetDisplay() override { return display_; }
    AudioCodec* GetAudioCodec() override { return audio_codec_; }

};

#endif //_MY_BOARD_H

#endif 