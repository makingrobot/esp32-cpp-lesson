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
#if APP_LESSON73_B == 1

#include "my_window2.h"
#include "src/framework/sys/log.h"

#define TAG "MyWindow2"

MyWindow2::MyWindow2() {
    Log::Info(TAG, "MyWindow2 constructor.");
}

void MyWindow2::Update() {
    Log::Info(TAG, "Update");

    uint16_t fg_color = random(0x10000);
    uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)

    uint16_t x = random(driver_->width());  // Position of centre of arc
    uint16_t y = random(driver_->height());

    uint8_t radius       = random(20, driver_->width() / 4); // Outer arc radius
    uint8_t thickness    = random(1, radius / 4);     // Thickness
    uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)

    // 0 degrees is at 6 o'clock position
    // Arcs are drawn clockwise from start_angle to end_angle
    // Start angle can be greater than end angle, the arc will then be drawn through 0 degrees
    uint16_t start_angle = random(361); // Start angle must be in range 0 to 360
    uint16_t end_angle   = random(361); // End angle must be in range 0 to 360

    bool smooth = random(2); // true = smooth sides, false = no smooth sides

    driver_->drawArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color, smooth);

}

#endif