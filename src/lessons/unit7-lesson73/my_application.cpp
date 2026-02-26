/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson73：TFT-LCD显示屏
 */
#include "config.h"
#if APP_LESSON73==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/display/tft_display.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {

}

void MyApplication::OnLoop() {

    delay(1);
}

#endif 