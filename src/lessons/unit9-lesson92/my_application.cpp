/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit9-Lesson92：文件系统应用
 */
#include "config.h"
#if APP_LESSON92==1

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
    WifiBoard *board = (WifiBoard*)(&Board::GetInstance());

    //一、使用热点
    //char *ssid = "esp32_ap";
    //bool success = board->StartAP(ssid, ap_ip, ap_gateway, ap_subnet);
    //std::string message = "AP:" + std::string(ssid) + ", IP:" + std::string(ap_ip.toString().c_str());
    
    //二、连接已有WiFi网络
    bool success = board->StartNetwork("ssid", "password", 10000);
    std::string message = "IP:" + board->GetIpAddress();
    
    if (success) {
        Log::Info(TAG, message.c_str());
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

    webserver_->on("/upload", HTTP_POST,
        [this]() { webserver_->send(200, "text/plain", ""); },
        [this]() { HandleFileUpload(); }
    );
    webserver_->onNotFound([this]() { HandleNotFound(); });

    webserver_->begin();

    webtask_ = new Task("WebServer");
    webtask_->OnLoop([this](){
        webserver_->handleClient();
        delay(1);
    });
    webtask_->Start(8192, tskIDLE_PRIORITY+1);
}

void MyApplication::HandleFileUpload() {
    FileSystem *fsys = Board::GetInstance().GetFileSystem();
    HTTPUpload &upload = webserver_->upload();
    if (upload.status == UPLOAD_FILE_START) {
        if (fsys->ExistsFile(upload.filename.c_str())) {
            fsys->DeleteFile(upload.filename.c_str());
        }
        uploadfile_ = fsys->OpenFile(upload.filename.c_str(), FILE_WRITE);
        Log::Info(TAG, "Upload: START, filename: %s", upload.filename);

    } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (uploadfile_) {
            uploadfile_.write(upload.buf, upload.currentSize);
        }
        Log::Info(TAG, "Upload: WRITE, Bytes: %ld", upload.currentSize);

    } else if (upload.status == UPLOAD_FILE_END) {
        if (uploadfile_) {
            uploadfile_.close();
        }
        Log::Info(TAG, "Upload: END, Size: %ld", upload.totalSize);
    }
}

void MyApplication::HandleNotFound() {
    FileSystem *fsys = Board::GetInstance().GetFileSystem(); 
    if (fsys == nullptr) {
        webserver_->send(500, "text/plain", "文件系统求初始化。");
        return;
    }

    String path = webserver_->uri();
    if (fsys->ExistsFile(path.c_str())) {
        OutputFile(path);
        return;
    }

    String message = "URI: ";
    message += webserver_->uri();
    message += "\nMethod: ";
    message += (webserver_->method() == HTTP_GET) ? "GET" : "POST";
    message += "\n";
    
    webserver_->send(404, "text/plain", message.c_str());
    Log::Warn(TAG, message.c_str());
}

void MyApplication::OutputFile(String path) {
    String dataType = "text/plain";
    if (path.endsWith("/")) {
        path += "index.htm";
    }

    if (path.endsWith(".htm") || path.endsWith(".html")) {
        dataType = "text/html";
    } else if (path.endsWith(".css")) {
        dataType = "text/css";
    } else if (path.endsWith(".js")) {
        dataType = "application/javascript";
    } else if (path.endsWith(".png")) {
        dataType = "image/png";
    } else if (path.endsWith(".gif")) {
        dataType = "image/gif";
    } else if (path.endsWith(".jpg")) {
        dataType = "image/jpeg";
    } else if (path.endsWith(".pdf")) {
        dataType = "application/pdf";
    } else if (path.endsWith(".zip")) {
        dataType = "application/zip";
    }

    FileSystem *fsys = Board::GetInstance().GetFileSystem(); 
    File f = fsys->OpenFile(path.c_str());
    webserver_->streamFile(f, dataType); // 输出文件内容
    f.close();
}

#endif 