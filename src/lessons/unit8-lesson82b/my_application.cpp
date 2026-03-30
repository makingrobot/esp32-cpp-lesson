/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson82：在网页上控制设备
 */
#include "config.h"
#if APP_LESSON82_B==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "src/framework/display/display.h"
#include "src/framework/led/led.h"
#include "my_board.h"
#include "html_content.h"

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
    WifiBoard *board = (WifiBoard*)(&Board::GetInstance());
    Display *display = Board::GetInstance().GetDisplay();
    display->Rotate(1);

    //一、使用热点
    char *ssid = "esp32_ap";
    bool success = board->StartAP(ssid, ap_ip, ap_gateway, ap_subnet);
    std::string message = "AP:" + std::string(ssid) + ", IP:" + std::string(ap_ip.toString().c_str());
    
    //二、连接已有WiFi网络
    // bool success = board->StartNetwork("ssid", "password", 10000);
    // std::string message = "IP:" + board->GetIpAddress();
    
    if (success) {
        Log::Info(TAG, message.c_str());
        display->GetWindow()->SetText(1, message);

        StartWebServer();
    } else {
        Log::Warn(TAG, "连接失败。");
        display->GetWindow()->SetText(1, "连接失败。");
    }
}

void MyApplication::OnLoop() {
    delay(1);
}

void MyApplication::StartWebServer() {
    webserver_ = new WebServer(80);

    // GET / 
    webserver_->on("/", [this](){ 
        int state = webserver_->arg("state").toInt();

        Led* led = Board::GetInstance().GetLed();
        if (state==1) {
            led->TurnOn();
        } else {
            led->TurnOff();
        }

        webserver_->send(200, "text/html", index_html);  // in html_content.h 
    });

    webserver_->begin();

    webtask_ = new FrtTask("WebServer");
    webtask_->OnLoop([this](){
        webserver_->handleClient();
        delay(1);
    });
    webtask_->Start(8192, tskIDLE_PRIORITY+1);
}

#endif 