/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson81：WiFi连接和HTTP请求
 */
#include "config.h"
#if APP_LESSON81==1

#include <Arduino.h>
#include <cJSON.h>
#include <HTTPClient.h>

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
        Log::Info(TAG, "IP: %s", board->GetIpAddress().c_str());
        GetServerData();
    } else {
        Log::Warn(TAG, "连接失败。");
    }
}

void MyApplication::OnLoop() {

    delay(1);
}

bool MyApplication::GetServerData() {
    std::string config_url = "https://www.xpstem.com/app/iot/project/productconfig";
    Log::Info(TAG, "access: %s", config_url.c_str());

    HTTPClient http;
    http.begin(String(config_url.c_str()));
    int status_code = http.GET();
    if (status_code != 200) {
        Log::Warn(TAG, "读取数据失败, 状态码: %d", status_code);
        return false;
    }

    String body = http.getString();
    http.end();

    // 解析
    cJSON *root_node = cJSON_Parse(body.c_str());
    if (!root_node) {
        const char *error = cJSON_GetErrorPtr();
        Log::Error(TAG, "解析数据错误，%s", error);
        return false;
    }

    int err_code = cJSON_GetObjectItem(root_node, "errCode")->valueint;
    if (err_code!=0) {
        std::string err_msg = cJSON_GetObjectItem(root_node, "errMsg")->valuestring;
        Log::Error(TAG, "获取数据失败，%s", err_msg.c_str());
        return false;
    }

    std::string data = cJSON_GetObjectItem(root_node, "data")->valuestring;
    Log::Info(TAG, "data: %s", data.c_str());
    return true;
}

#endif 