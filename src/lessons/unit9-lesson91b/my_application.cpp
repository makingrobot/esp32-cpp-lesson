/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
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

    char *path = "/001.mp3";
    if (fsys->ExistsFile(path)) {
        Log::Info(TAG, "read file.");
        File f = fsys->OpenFile(path);
        if (f) {
            Log::Info(TAG, "File %s size: %d ", path, f.size());
            uint8_t buf[1025] = { 0 };
            size_t bytes_read = f.read(buf, 1024);
            Log::Info(TAG, "read %d bytes ok", bytes_read);
        } else {
            Log::Warn(TAG, "File %s op failed.", path);
        }
    } else {
        Log::Info(TAG, "file not exists.");
    }
}

void MyApplication::OnLoop() {
    
}

#endif 