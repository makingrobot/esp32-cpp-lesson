/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson63：多线程和同步
 */
#include "config.h"
#if APP_LESSON63==1

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/peripheral/actuator.h"
#include "src/framework/peripheral/switch_actuator.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new ExampleApp();
}

ExampleApp::ExampleApp() : Application() { 

}

void ExampleApp::OnInit() {
    
}

void ExampleApp::OnLoop() {

    delay(1);
}


#endif 