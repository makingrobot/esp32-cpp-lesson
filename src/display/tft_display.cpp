/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_USE_TFT_ESPI == 1

#include "tft_display.h"
#include "src/sys/log.h"

#define TAG "TftDisplay"

TftDisplay::TftDisplay(TFT_eSPI* driver, int width, int height) {
            
    Log::Debug(TAG, "TftDisplay constructor.");

    driver_ = driver;
    width_ = width;
    height_ = height;

}

TftDisplay::~TftDisplay() {

}

bool TftDisplay::Lock(int timeout_ms) {
    return true;
}
 
void TftDisplay::Unlock() {
}

void TftDisplay::Init() {

    driver_->setTextColor(TFT_WHITE);
   
}
    
void TftDisplay::SetStatus(const std::string& status) {

    status_ = status;
    driver_->setCursor(4, 20, 2);
    driver_->println(status_.c_str());
}

void TftDisplay::SetText(const std::string& text) {
    text_ = text;
    driver_->setCursor(4, 60, 4);
    driver_->println(text_.c_str());
}

#endif //CONFIG_USE_TFT_ESPI