/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson72：OLED显示屏
 */
#include "config.h"
#if APP_LESSON72==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/display/u8g2_display.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    U8g2Display* display = (U8g2Display*)(Board::GetInstance().GetDisplay());
    display->GetWindow()->SetText(1, "你好，世界!");
}

void MyApplication::OnLoop() {
    count_++;
    U8g2Display* display = (U8g2Display*)(Board::GetInstance().GetDisplay());
    display->GetWindow()->SetText(2, "计数: " + std::to_string(count_));
    delay(1000);
}

#endif 