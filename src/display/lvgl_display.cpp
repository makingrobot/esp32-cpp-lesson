/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_USE_LVGL == 1

#include "lvgl_display.h"

#include <vector>
#include <algorithm>
#include <esp_err.h>
#include <esp_heap_caps.h>
#include <cstring>
#include <esp_log.h>

#include "src/libs/esp_lvgl_port/esp_lvgl_port.h"
#include "src/sys/settings.h"
#include "src/boards/board.h"
#include "src/fonts/font_awesome_symbols.h"
#include "src/lang/lang_zh_cn.h"
#include "src/app/device_state.h"
#include "src/app/application.h"
#include "src/sys/time.h"

#define TAG "LvglDisplay"

LvglDisplay::LvglDisplay(LcdDriver* driver, DisplayFonts fonts)
        : driver_(driver), fonts_(fonts) {
            
    ESP_LOGD(TAG, "LvglDisplay constructor.");

    width_ = driver->width();
    height_ = driver->height();

    // Load theme from settings
    Settings settings("display", false);
    current_theme_name_ = settings.GetString("theme", "light");

    // Update the theme
    if (current_theme_name_ == "dark") {
        current_theme_ = DARK_THEME;
    } else if (current_theme_name_ == "light") {
        current_theme_ = LIGHT_THEME;
    }

    notification_ticker_ = new Ticker();

    driver_->InitLvgl();
}

LvglDisplay::~LvglDisplay() {

    if( notification_ticker_!=nullptr ) {
        notification_ticker_->detach();
        notification_ticker_=nullptr;
    }

    if (content_ != nullptr) {
        lv_obj_del(content_);
    }
    if (status_bar_ != nullptr) {
        lv_obj_del(status_bar_);
    }
    if (side_bar_ != nullptr) {
        lv_obj_del(side_bar_);
    }
    if (container_ != nullptr) {
        lv_obj_del(container_);
    }

    if (network_label_ != nullptr) {
        lv_obj_del(network_label_);
        lv_obj_del(notification_label_);
        lv_obj_del(status_label_);
        lv_obj_del(mute_label_);
        lv_obj_del(battery_label_);
    }
    if (time_label_ != nullptr) {
        lv_obj_del(time_label_);
    }
    if (text_label_ != nullptr) {
        lv_obj_del(text_label_);
    }
    if( low_battery_popup_ != nullptr ) {
        lv_obj_del(low_battery_popup_);
    }

    driver_ = nullptr;
}

void LvglDisplay::SetupUI() {
    ESP_LOGI(TAG, "SetupUI ......");

    DisplayLockGuard lock(this);

    auto screen = lv_screen_active();
    lv_obj_set_style_text_font(screen, fonts_.text_font, 0);
    lv_obj_set_style_text_color(screen, current_theme_.text, 0);
    lv_obj_set_style_bg_color(screen, current_theme_.background, 0);

    /* Container */
    container_ = lv_obj_create(screen);
    lv_obj_set_size(container_, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_flex_flow(container_, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(container_, 0, 0);
    lv_obj_set_style_border_width(container_, 0, 0);
    lv_obj_set_style_pad_row(container_, 0, 0);
    lv_obj_set_style_bg_color(container_, current_theme_.background, 0);
    lv_obj_set_style_border_color(container_, current_theme_.border, 0);

    /* Status bar */
    status_bar_ = lv_obj_create(container_);
    lv_obj_set_size(status_bar_, LV_HOR_RES, fonts_.text_font->line_height);
    lv_obj_set_style_radius(status_bar_, 0, 0);
    lv_obj_set_style_bg_color(status_bar_, current_theme_.background, 0);
    lv_obj_set_style_text_color(status_bar_, current_theme_.text, 0);
    
    lv_obj_set_flex_flow(status_bar_, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(status_bar_, 0, 0);
    lv_obj_set_style_border_width(status_bar_, 0, 0);
    lv_obj_set_style_pad_column(status_bar_, 0, 0);
    lv_obj_set_style_pad_left(status_bar_, 2, 0);
    lv_obj_set_style_pad_right(status_bar_, 2, 0);

    time_label_ = lv_label_create(status_bar_);
    lv_obj_set_flex_grow(time_label_, 1);
    lv_obj_set_style_text_color(time_label_, current_theme_.text, 0);
    lv_label_set_text(time_label_, "");

    notification_label_ = lv_label_create(status_bar_);
    lv_obj_set_flex_grow(notification_label_, 1);
    lv_obj_set_style_text_align(notification_label_, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(notification_label_, current_theme_.text, 0);
    lv_label_set_text(notification_label_, "");
    lv_obj_add_flag(notification_label_, LV_OBJ_FLAG_HIDDEN);

    status_label_ = lv_label_create(status_bar_);
    lv_obj_set_flex_grow(status_label_, 1);
    lv_label_set_long_mode(status_label_, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_align(status_label_, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(status_label_, current_theme_.text, 0);
    lv_label_set_text(status_label_, Lang::Strings::INITIALIZING);

    network_label_ = lv_label_create(status_bar_);
    lv_label_set_text(network_label_, "");
    lv_obj_set_style_text_font(network_label_, fonts_.icon_font, 0);
    lv_obj_set_style_text_color(network_label_, current_theme_.text, 0);

    mute_label_ = lv_label_create(status_bar_);
    lv_label_set_text(mute_label_, "");
    lv_obj_set_style_text_font(mute_label_, fonts_.icon_font, 0);
    lv_obj_set_style_text_color(mute_label_, current_theme_.text, 0);

    battery_label_ = lv_label_create(status_bar_);
    lv_label_set_text(battery_label_, "");
    lv_obj_set_style_text_font(battery_label_, fonts_.icon_font, 0);
    lv_obj_set_style_text_color(battery_label_, current_theme_.text, 0);

    low_battery_popup_ = lv_obj_create(screen);
    lv_obj_set_scrollbar_mode(low_battery_popup_, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_size(low_battery_popup_, LV_HOR_RES * 0.9, fonts_.text_font->line_height * 2);
    lv_obj_align(low_battery_popup_, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(low_battery_popup_, current_theme_.low_battery, 0);
    lv_obj_set_style_radius(low_battery_popup_, 10, 0);

    low_battery_label_ = lv_label_create(low_battery_popup_);
    lv_label_set_text(low_battery_label_, Lang::Strings::BATTERY_NEED_CHARGE);
    lv_obj_set_style_text_color(low_battery_label_, lv_color_white(), 0);
    lv_obj_center(low_battery_label_);
    lv_obj_add_flag(low_battery_popup_, LV_OBJ_FLAG_HIDDEN);

    /* Content */
    content_ = lv_obj_create(container_);
    lv_obj_set_scrollbar_mode(content_, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(content_, 0, 0);
    lv_obj_set_width(content_, LV_HOR_RES);
    lv_obj_set_flex_grow(content_, 1);
    lv_obj_set_style_pad_all(content_, 5, 0);
    lv_obj_set_style_bg_color(content_, current_theme_.chat_background, 0);
    lv_obj_set_style_border_color(content_, current_theme_.border, 0); // Border color for content

    lv_obj_set_flex_flow(content_, LV_FLEX_FLOW_COLUMN); // 垂直布局（从上到下）
    lv_obj_set_flex_align(content_, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY); // 子对象居中对齐，等距分布

    text_label_ = lv_label_create(content_);
    lv_label_set_text(text_label_, "");
    lv_obj_set_width(text_label_, LV_HOR_RES * 0.9); // 限制宽度为屏幕宽度的 90%
    lv_label_set_long_mode(text_label_, LV_LABEL_LONG_WRAP); // 设置为自动换行模式
    lv_obj_set_style_text_align(text_label_, LV_TEXT_ALIGN_CENTER, 0); // 设置文本居中对齐
    lv_obj_set_style_text_color(text_label_, current_theme_.text, 0);

    ESP_LOGI( TAG, "SetupUI completed." );
}

bool LvglDisplay::Lock(int timeout_ms) {
    return lvgl_port_lock(timeout_ms);
}

void LvglDisplay::Unlock() {
    lvgl_port_unlock();
}

void LvglDisplay::SetTheme(const std::string& theme_name) {
    DisplayLockGuard lock(this);
    
    if (theme_name == "dark" || theme_name == "DARK") {
        current_theme_ = DARK_THEME;
    } else if (theme_name == "light" || theme_name == "LIGHT") {
        current_theme_ = LIGHT_THEME;
    } else {
        // Invalid theme name, return false
        ESP_LOGE( TAG, "Invalid theme name: %s", theme_name.c_str());
        return;
    }
    
    // Get the active screen
    lv_obj_t* screen = lv_screen_active();
    
    // Update the screen colors
    lv_obj_set_style_bg_color(screen, current_theme_.background, 0);
    lv_obj_set_style_text_color(screen, current_theme_.text, 0);
    
    // Update container colors
    if (container_ != nullptr) {
        lv_obj_set_style_bg_color(container_, current_theme_.background, 0);
        lv_obj_set_style_border_color(container_, current_theme_.border, 0);
    }
    
    // Update status bar colors
    if (status_bar_ != nullptr) {
        lv_obj_set_style_bg_color(status_bar_, current_theme_.background, 0);
        lv_obj_set_style_text_color(status_bar_, current_theme_.text, 0);
        
        // Update status bar elements
        if (network_label_ != nullptr) {
            lv_obj_set_style_text_color(network_label_, current_theme_.text, 0);
        }
        if (status_label_ != nullptr) {
            lv_obj_set_style_text_color(status_label_, current_theme_.text, 0);
        }
        if (notification_label_ != nullptr) {
            lv_obj_set_style_text_color(notification_label_, current_theme_.text, 0);
        }
        if (mute_label_ != nullptr) {
            lv_obj_set_style_text_color(mute_label_, current_theme_.text, 0);
        }
        if (battery_label_ != nullptr) {
            lv_obj_set_style_text_color(battery_label_, current_theme_.text, 0);
        }
    }
    
    // Update content area colors
    if (content_ != nullptr) {
        lv_obj_set_style_bg_color(content_, current_theme_.chat_background, 0);
        lv_obj_set_style_border_color(content_, current_theme_.border, 0);
        lv_obj_set_style_text_color(text_label_, current_theme_.text, 0);
    }
    
    // Update low battery popup
    if (low_battery_popup_ != nullptr) {
        lv_obj_set_style_bg_color(low_battery_popup_, current_theme_.low_battery, 0);
    }
}

void LvglDisplay::SetText(const char* text) {
    DisplayLockGuard lock(this);
    if (text_label_ == nullptr) {
        ESP_LOGW(TAG, "text label not setup.");
        return;
    }
    lv_label_set_text(text_label_, text);
}

void LvglDisplay::SetStatus(const char* status) {
    DisplayLockGuard lock(this);
    if (status_label_ == nullptr) {
        return;
    }
    lv_label_set_text(status_label_, status);
    lv_obj_clear_flag(status_label_, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(notification_label_, LV_OBJ_FLAG_HIDDEN);

    last_status_update_time_ = std::chrono::system_clock::now();
}

void LvglDisplay::ShowNotification(const std::string &notification, int duration_ms) {
    ShowNotification(notification.c_str(), duration_ms);
}

void TickerCallback(LvglDisplay *arg) {
    arg->OnNotificationTimer();
}

void LvglDisplay::ShowNotification(const char* notification, int duration_ms) {
    DisplayLockGuard lock(this);
    if (notification_label_ == nullptr) {
        return;
    }
    lv_label_set_text(notification_label_, notification);
    lv_obj_clear_flag(notification_label_, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(status_label_, LV_OBJ_FLAG_HIDDEN);

    notification_ticker_->once(1, TickerCallback, this);
    ESP_LOGI( TAG, "notification timer started" );
}

void LvglDisplay::OnNotificationTimer() {
    DisplayLockGuard lock(this);
    lv_obj_add_flag(notification_label_, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(status_label_, LV_OBJ_FLAG_HIDDEN);
}

void LvglDisplay::UpdateStatusBar(bool update_all) {
    
    auto& board = Board::GetInstance();

#if CONFIG_USE_AUDIO==1
    {
        DisplayLockGuard lock(this);
        if (mute_label_ == nullptr) {
            return;
        }

        AudioCodec* codec = board.GetAudioCodec();
        // 如果静音状态改变，则更新图标
        if (codec->output_volume() == 0 && !muted_) {
            muted_ = true;
            lv_label_set_text(mute_label_, FONT_AWESOME_VOLUME_MUTE);
        } else if (codec->output_volume() > 0 && muted_) {
            muted_ = false;
            lv_label_set_text(mute_label_, "");
        }
    }
#endif //CONFIG_USE_AUDIO

    static int seconds_counter = 0;

    // Update time
    // Time* time = board.GetTime();
    // if (time != nullptr) {
    //     time->Update();
    //     lv_label_set_text(time_label_, time->GetHourMinute().c_str());
    // }
    // if (last_status_update_time_ + std::chrono::seconds(10) < std::chrono::system_clock::now()) {
    //     // Set status to clock "HH:MM"
    //     time_t now = time(NULL);
    //     struct tm* tm = localtime(&now);
    //     // Check if the we have already set the time
    //     if (tm->tm_year >= 2025 - 1900) {
    //         char time_str[16];
    //         strftime(time_str, sizeof(time_str), "%H:%M  ", tm);
    //         SetStatus(time_str);
    //     } else {
    //         // 每 60 秒输出一次
    //         if (seconds_counter++ % 60 == 0) {
    //             ESP_LOGW( TAG, "System time is not set, tm_year: %d", tm->tm_year);
    //         }
    //     }
    // }

    // 更新电池图标
    int battery_level;
    bool charging, discharging;
    const char* icon = nullptr;
    if (board.GetBatteryLevel(battery_level, charging, discharging)) {
        if (charging) {
            icon = FONT_AWESOME_BATTERY_CHARGING;
        } else {
            const char* levels[] = {
                FONT_AWESOME_BATTERY_EMPTY, // 0-19%
                FONT_AWESOME_BATTERY_1,    // 20-39%
                FONT_AWESOME_BATTERY_2,    // 40-59%
                FONT_AWESOME_BATTERY_3,    // 60-79%
                FONT_AWESOME_BATTERY_FULL, // 80-99%
                FONT_AWESOME_BATTERY_FULL, // 100%
            };
            icon = levels[battery_level / 20];
        }
        DisplayLockGuard lock(this);
        if (battery_label_ != nullptr && battery_icon_ != icon) {
            battery_icon_ = icon;
            lv_label_set_text(battery_label_, battery_icon_);
        }

        if (low_battery_popup_ != nullptr) {
            if (strcmp(icon, FONT_AWESOME_BATTERY_EMPTY) == 0 && discharging) {
                if (lv_obj_has_flag(low_battery_popup_, LV_OBJ_FLAG_HIDDEN)) { // 如果低电量提示框隐藏，则显示
                    lv_obj_clear_flag(low_battery_popup_, LV_OBJ_FLAG_HIDDEN);
                }
            } else {
                // Hide the low battery popup when the battery is not empty
                if (!lv_obj_has_flag(low_battery_popup_, LV_OBJ_FLAG_HIDDEN)) { // 如果低电量提示框显示，则隐藏
                    lv_obj_add_flag(low_battery_popup_, LV_OBJ_FLAG_HIDDEN);
                }
            }
        }
    }

    //每 10 秒更新一次网络图标
    if (update_all || seconds_counter++ % 10 == 0) {
        // 升级固件时，不读取 4G 网络状态，避免占用 UART 资源
        DeviceState* device_state = Application::GetInstance().GetDeviceState();
        if (device_state->state() == kDeviceStateIdle->state() ||
                device_state->state() == kDeviceStateStarting->state() ||
                device_state->state() == kDeviceStateWifiConfiguring->state() || 
                device_state->state() == kDeviceStateWorking->state()) {
            const char* icon = GetWifiIcon();
            if (network_label_ != nullptr && icon != nullptr && network_icon_ != icon) {
                DisplayLockGuard lock(this);
                network_icon_ = icon;
                lv_label_set_text(network_label_, network_icon_);
            }
        }
    }

}

const char* LvglDisplay::GetWifiIcon() {
    auto& board = Board::GetInstance();
    const char* icon_name = board.GetNetworkStateIconName();
    if (strcmp(icon_name, "WIFI") == 0) {
        return FONT_AWESOME_WIFI;
    } else if (strcmp(icon_name, "WIFI_FAIR") == 0) {
        return FONT_AWESOME_WIFI_FAIR;
    } else if (strcmp(icon_name, "WIFI_WEAK") == 0) {
        return FONT_AWESOME_WIFI_WEAK;
    } else if (strcmp(icon_name, "WIFI_OFF") == 0) {
        return FONT_AWESOME_WIFI_OFF;
    }
    return nullptr;
}

#endif // CONFIG_USE_LVGL
