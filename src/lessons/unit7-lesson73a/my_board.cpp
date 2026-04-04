/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit7-Lesson73：TFT-LCD显示屏
 */
#include "config.h"
#if APP_LESSON73_A == 1

#include <Arduino.h>
#include <SPI.h>
#include "src/framework/display/tft_display.h"

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    InitDisplay();
    
    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::InitDisplay() {
    Log::Info( TAG, "Init st7789 display ......" );
    /**
     * 注意！！！
     * 请在TFT_eSPI库包内的User_Setup.h中配置引脚
     */
    TFT_eSPI *tft_espi = new TFT_eSPI(DISPLAY_HEIGHT, DISPLAY_WIDTH);
    tft_espi->invertDisplay(DISPLAY_INVERT_COLOR);
    
    //u8g2_font_unifont_t_chinese2
    display_ = new TftDisplay(tft_espi, DISPLAY_HEIGHT, DISPLAY_WIDTH);
}

#endif 