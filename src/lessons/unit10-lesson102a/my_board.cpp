/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson102：音频录制
 */
#include "config.h"
#if BOARD_LESSON102_A == 1

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/board/onebutton_impl.h"
#include "src/framework/app/application.h"
#include "src/framework/display/tft_display.h"
#include "audio_i2s_sph0645.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    std::shared_ptr<Button> button1 = std::make_shared<OneButtonImpl>(kManualButton, MANUAL_BUTTON_PIN, false);
    button1->BindAction(ButtonAction::DoubleClick);
    AddButton(button1);

    InitDisplay();
    InitFileSystem();
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

void MyBoard::InitFileSystem() {
    Log::Info(TAG, "initial file system.");
    SPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    if (!SD.begin(SD_CS_PIN)) {
        Log::Info(TAG, "SD Mount Failed");
        return;
    }

    filesystem_ = new FileSystem(SD);
    filesystem_->setTotalBytes(SD.totalBytes());
    filesystem_->setFreeBytes(SD.totalBytes() - SD.usedBytes());
    filesystem_->setType("SD");

    Log::Info(TAG, "init filesystem, type: %s, totalbytes: %ld, freebytes: %ld", 
            filesystem_->type().c_str(), filesystem_->totalBytes(), filesystem_->freeBytes());
}

void MyBoard::InitAudioCodec() {
    Log::Info(TAG, "initial audio codec.");
    audio_codec_ = new AudioI2sSph0645(MIC_BCLK_PIN, MIC_WS_PIN, MIC_DIN_PIN);
}

void MyBoard::ButtonTick() {
    for (const auto& pair : button_map()) {
        pair.second->Tick();
    }
}

#endif 