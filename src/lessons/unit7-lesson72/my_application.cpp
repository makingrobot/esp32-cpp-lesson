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
#if APP_LESSON72==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    Display* display = Board::GetInstance().GetDisplay();
    display->GetWindow()->SetText(1, "你好，世界!");
}

void MyApplication::OnLoop() {
    count_++;
    Display* display = Board::GetInstance().GetDisplay();
    display->GetWindow()->SetText(2, "计数: " + std::to_string(count_));
    delay(1000);
}

#endif 