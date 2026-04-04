/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit7-Lesson72：OLED显示屏
 */
#include "config.h"
#if APP_LESSON72 == 1

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"
#include "src/framework/display/u8g2_display.h"

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
    Log::Info( TAG, "Init ssd1306 display ......" );
    U8G2 *u8g2 = new U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R0, 
        /* i2c clk */ I2C_SCL_PIN,
        /* i2c data */ I2C_SDA_PIN,
        /* reset=*/ U8X8_PIN_NONE
    );
    u8g2->setI2CAddress(OLED_I2C_ADDRESS << 1);

    //u8g2_font_unifont_t_chinese2
    display_ = new U8g2Display(u8g2, DISPLAY_WIDTH, DISPLAY_HEIGHT, u8g2_font_wqy14_t_gb2312);
}

#endif 