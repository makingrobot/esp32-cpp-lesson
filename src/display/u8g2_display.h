/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_USE_U8G2 == 1

#ifndef _U8G2_DISPLAY_H
#define _U8G2_DISPLAY_H

#include "display.h"
#include <U8g2lib.h>

class U8g2Display : public Display {
public:
    U8g2Display(U8G2* u8g2, int width, int height, const uint8_t* fonts);
    virtual ~U8g2Display();

    void Init() override;
    
    void SetStatus(const char* status) override;
    void SetText(const char* text) override;
   
    const U8G2* u8g2() const { return driver_; }

protected:
    bool Lock(int timeout_ms = 0) override;
    void Unlock() override;

private:
    U8G2* driver_ = nullptr;
    const uint8_t* fonts_ = nullptr;

    const char* status_ = "";
    const char* text_ = "";

    void Update();
};

#endif //_U8G2_DISPLAY_H

#endif //_CONFIG_USE_U8G2