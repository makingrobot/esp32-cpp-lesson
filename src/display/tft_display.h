/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_USE_TFT_ESPI == 1

#ifndef _TFT_DISPLAY_H
#define _TFT_DISPLAY_H

#include "display.h"
#include <TFT_eSPI.h>

class TftDisplay : public Display {
public:
    TftDisplay(TFT_eSPI *driver_, int width, int height);
    virtual ~TftDisplay();

    virtual void Setup();
    
    void SetStatus(const char* status) override;
    void SetText(const char* text) override;
   
    const TFT_eSPI* tft() const { return driver_; }

protected:
    bool Lock(int timeout_ms = 0) override;
    void Unlock() override;

private:
    TFT_eSPI *driver_ = nullptr;
};

#endif //_TFT_DISPLAY_H

#endif //CONFIG_USE_TFT_ESPI