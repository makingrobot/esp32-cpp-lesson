/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_MP3==1

#ifndef MP3_DISPLAY_H
#define MP3_DISPLAY_H

#include <lvgl.h>
#include "src/display/lcd_driver.h"
#include "src/display/lvgl_display.h"

class Mp3Display : public LvglDisplay {
protected:
    lv_obj_t* emotion_label_ = nullptr;

    void SetupUI() override;
    
public:
    Mp3Display(LcdDriver* driver, DisplayFonts fonts);
    ~Mp3Display();

    void SetTheme(const std::string& theme_name) override;
    void SetContent(const char *content);

private:
    lv_obj_t* content_label_ = nullptr;

};

#endif // MY_DISPLAY_H

#endif //APP_DEMO_MP3