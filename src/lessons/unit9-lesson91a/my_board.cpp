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
#if BOARD_LESSON91_A == 1

#include <Wire.h>
#include <FFat.h>

#include "board_config.h"
#include "my_board.h"
#include "src/framework/led/gpio_led.h"
#include "src/framework/app/application.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    Log::Info(TAG, "initial led.");
    led_ = new GpioLed(BUILTIN_LED_PIN, false); // no pwm

    InitFileSystem();
    
    Log::Info( TAG, "===== Board config completed. =====");
}

void MyBoard::InitFileSystem() {
    if (!FFat.begin()) {
        FFat.format();
        if (!FFat.begin()) {
            Log::Info(TAG, "FFat Mount Failed");
            return;
        }
    }

    filesystem_ = new FileSystem(FFat);
    filesystem_->setTotalBytes(FFat.totalBytes());
    filesystem_->setFreeBytes(FFat.freeBytes());
    filesystem_->setType("ffat");

    Log::Info(TAG, "init filesystem, type: %s, totalbytes: %ld, freebytes: %ld", 
            filesystem_->type(), filesystem_->totalBytes(), filesystem_->freeBytes());
}

#endif 