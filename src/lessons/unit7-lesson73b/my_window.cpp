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

#include "my_window.h"
#include "src/framework/sys/log.h"

#define TAG "MyWindow"

MyWindow::MyWindow() {
    Log::Info(TAG, "MyWindow constructor.");
}

void MyWindow::Update() {
    Log::Info(TAG, "Update");

    // Fill screen with grey so we can see the effect of printing with and without 
    // a background colour defined
    driver_->fillScreen(TFT_DARKGREY);
    
    // Set "cursor" at top left corner of display (0,0) and select font 2
    // (cursor will move to next line automatically during printing with 'tft.println'
    //  or stay on the line is there is room for the text with tft.print)
    driver_->setCursor(0, 0, 2);
    // Set the font colour to be white with a black background, set text size multiplier to 1
    driver_->setTextColor(TFT_WHITE,TFT_BLACK);  
    driver_->setTextSize(1);
    // We can now plot text on screen using the "print" class
    driver_->println("Hello World!");
    
    // Set the font colour to be yellow with no background, set to font 7
    driver_->setTextColor(TFT_YELLOW); 
    driver_->setTextFont(7);
    driver_->println(1234.56);
    
    // Set the font colour to be red with black background, set to font 4
    driver_->setTextColor(TFT_RED,TFT_BLACK);    
    driver_->setTextFont(4);
    //tft.println(3735928559L, HEX); // Should print DEADBEEF

    // Set the font colour to be green with black background, set to font 4
    driver_->setTextColor(TFT_GREEN,TFT_BLACK);
    driver_->setTextFont(4);
    driver_->println("Groop");
    driver_->println("I implore thee,");

    // Change to font 2
    driver_->setTextFont(2);
    driver_->println("my foonting turlingdromes.");
    driver_->println("And hooptiously drangle me");
    driver_->println("with crinkly bindlewurdles,");
    // This next line is deliberately made too long for the display width to test
    // automatic text wrapping onto the next line
    driver_->println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");
    
    // Test some print formatting functions
    float fnumber = 123.45;
    // Set the font colour to be blue with no background, set to font 4
    driver_->setTextColor(TFT_BLUE);    
    driver_->setTextFont(4);
    driver_->print("Float = "); 
    driver_->println(fnumber);           // Print floating point number
    driver_->print("Binary = "); 
    driver_->println((int)fnumber, BIN); // Print as integer value in binary
    driver_->print("Hexadecimal = "); 
    driver_->println((int)fnumber, HEX); // Print as integer number in Hexadecimal

}

#endif