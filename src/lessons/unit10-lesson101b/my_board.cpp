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

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/display/tft_display.h"
#include "src/framework/audio/codec/audio_i2s_simplex.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : WifiBoard() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    InitDisplay();
    InitAudioCodec();

    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::InitDisplay() {
    Log::Info( TAG, "Init tft display ......" );
    /**
     * 注意！！！
     * 请在TFT_eSPI库包内的User_Setup.h中配置引脚
     */
    TFT_eSPI *tft_espi = new TFT_eSPI(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    //tft_espi_->invertDisplay(DISPLAY_INVERT_COLOR);
    
    //u8g2_font_unifont_t_chinese2
    display_ = new TftDisplay(tft_espi, DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

void MyBoard::InitAudioCodec() {
    Log::Info(TAG, "initial audio codec.");
    audio_codec_ = new AudioI2sSimplexSpeaker(SPK_BCLK_PIN, SPK_WS_PIN, SPK_DOUT_PIN);
}

#endif 