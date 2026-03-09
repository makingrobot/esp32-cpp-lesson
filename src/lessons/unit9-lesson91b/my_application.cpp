/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit9-Lesson91：文件系统
 */
#include "config.h"
#if APP_LESSON91_B==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/file/file_system.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    FileSystem *fsys = Board::GetInstance().GetFileSystem();
    if (fsys==nullptr) {
        Log::Warn(TAG, "FileSystem init failed.");
        return;
    }

    char *path = "/hello.txt";
    if (fsys->ExistsFile(path)) {
        Log::Info(TAG, "read file.");
        File f = fsys->OpenFile(path);
        if (f) {
            String content = f.readString();
            Serial.println(content);
        } else {
            Log::Warn(TAG, "File %s read failed.", path);
        }
    } else {
        Log::Info(TAG, "create file.");
        fsys->WriteFile(path, "Hello world!");
    }
}

void MyApplication::OnLoop() {
    
}

#endif 