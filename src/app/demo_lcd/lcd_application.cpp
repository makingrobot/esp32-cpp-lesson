/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_LCD==1

#include "lcd_application.h"
#include "esp_log.h"
#include "src/boards/board.h"
#include "src/lang/lang_zh_cn.h"
#include "src/display/lvgl_display.h"

#define TAG "LcdApplication"

void* create_application() {
    return new LcdApplication();
}

LcdApplication::LcdApplication() : Application() { 

    Board& board = Board::GetInstance();

    ESP_LOGI( TAG, "Create display." );
    LcdDriver* driver = dynamic_cast<LcdDriver*>(board.GetDispDriver());
    LvglDisplay *my_disp = new LvglDisplay(driver, 
                                {
                                    .text_font = &font_puhui_20_4,
                                    .icon_font = &font_awesome_16_4,
                                    .emoji_font = font_emoji_32_init(),
                                });
    board.SetDisplay(my_disp);
}

LcdApplication::~LcdApplication() {
   
}

void LcdApplication::Init() {
    Application::Init();
    
    // do your init.
}

void LcdApplication::Start() {
    Application::Start();

    Board& board = Board::GetInstance();
    board.GetDisplay()->SetText("Hello world!");
}

#endif //APP_DEMO_LCD