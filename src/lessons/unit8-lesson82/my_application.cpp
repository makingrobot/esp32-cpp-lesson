/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson82：
 */
#include "config.h"
#if APP_LESSON82==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "src/framework/display/tft_display.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    WifiBoard *board = (WifiBoard*)(&Board::GetInstance());
    bool connected = board->StartNetwork("ssid", "password", 10000);
    if (connected) {
        StartWebServer();
    } else {
        Log::Warn(TAG, "连接失败。");
    }
}

void MyApplication::OnLoop() {

    delay(1);
}

void MyApplication::StartWebServer() {
    webserver_ = new WebServer(80);

    // GET / 
    webserver_->on("/", [this](){ 
        webserver_->send(200, "text/html", "<h3>It's works</h3>"); 
    });

    webserver_->begin();

    webtask_ = new Task("WebServer");
    webtask_->OnLoop([](void* parameter){
        WebServer *server = (WebServer*)parameter;
        server->handleClient();
        delay(1);
    }, webserver_);
    webtask_->Start(8192, tskIDLE_PRIORITY+1);
}

#endif 