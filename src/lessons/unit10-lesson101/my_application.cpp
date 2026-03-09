/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson101：音频输出
 */
#include "config.h"
#if APP_LESSON101==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "my_board.h"

#define TAG "MyApplication"

static const IPAddress ap_ip(192,168,5,1);
static const IPAddress ap_gateway(192,168,5,1);
static const IPAddress ap_subnet(255,255,255,0);

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    
    // 建立一个音频管道

    // 添加音频输入

    // 添加音频输出

    // 启动管道
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 