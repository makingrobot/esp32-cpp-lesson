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
#include "src/framework/display/display.h"
#include "src/framework/file/file_system.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    Display *display = Board::GetInstance().GetDisplay();
    display->Rotate(1);

    FileSystem *fsys = Board::GetInstance().GetFileSystem();
    if (fsys==nullptr) {
        Log::Warn(TAG, "FileSystem init failed.");
        display->GetWindow()->SetText(1, "FileSystem init failed.");
        return;
    }

    display->GetWindow()->SetText(1, "filesystem type: "+ fsys->type());

    char *path = "/hello.txt";
    if (fsys->ExistsFile(path)) {
        Log::Info(TAG, "read file.");
        File f = fsys->OpenFile(path);
        if (f) {
            String content = f.readString();
            
            display->GetWindow()->SetText(2, "File read success.");
            display->GetWindow()->SetText(3, std::string(content.c_str()));
        } else {
            Log::Warn(TAG, "File %s read failed.", path);
            display->GetWindow()->SetText(2, "File read failed.");
        }
    } else {
        Log::Info(TAG, "create file.");
        fsys->WriteFile(path, "Hello world!");
        display->GetWindow()->SetText(2, "File create success.");
    }
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 