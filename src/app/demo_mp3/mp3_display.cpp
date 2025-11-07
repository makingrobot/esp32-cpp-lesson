/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_MP3==1

#include "mp3_display.h"

#include <vector>
#include <algorithm>
#include <esp_err.h>
#include <esp_heap_caps.h>
#include <cstring>

#include "esp_log.h"
#include "src/libs/esp_lvgl_port/esp_lvgl_port.h"

#include "src/sys/settings.h"
#include "src/boards/board.h"
#include "src/display/lvgl_display.h"
#include "src/fonts/font_awesome_symbols.h"
#include "src/lang/lang_zh_cn.h"

#define TAG "Mp3Display"

Mp3Display::Mp3Display(LcdDriver* driver, DisplayFonts fonts)
    : LvglDisplay(driver, fonts) {

    ESP_LOGD(TAG, "Mp3Display constructor.");
}

Mp3Display::~Mp3Display() {

    if (content_label_ != nullptr) {
        lv_obj_del(content_label_);
    }

}

void Mp3Display::SetupUI() {
    ESP_LOGD(TAG, "SetupUI ......");

    LvglDisplay::SetupUI();

    content_label_ = lv_label_create(content_);
    lv_obj_set_width(content_label_, LV_HOR_RES * 0.9); // 限制宽度为屏幕宽度的 90%
    lv_obj_set_style_text_align(content_label_, LV_TEXT_ALIGN_CENTER, 0); // 设置文本居中对齐
    lv_obj_set_style_text_color(content_label_, current_theme_.text, 0);
    lv_label_set_text(content_label_, "");

    ESP_LOGD( TAG, "SetupUI completed." );
}


void Mp3Display::SetTheme(const std::string& theme_name) {
    ESP_LOGD(TAG, "entering SetTheme.");

    LvglDisplay::SetTheme(theme_name);
    
    // Update content area colors
    if (content_ != nullptr) {
        ESP_LOGW(TAG, "content not setup.");

        if (content_label_ != nullptr) {
            lv_obj_set_style_text_color(content_label_, current_theme_.text, 0);
        }
    }
    
}

void Mp3Display::SetContent(const char *content) {
    
    DisplayLockGuard lock(this);
    
    if (content_label_ == nullptr) {
        ESP_LOGW(TAG, "content label not setup.");
        return;
    }
    lv_label_set_text(content_label_, content);
    
}

#endif //APP_DEMO_MP3

