/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if BOARD_LESSON01 == 1

#include "board_config.h"
#include "my_board.h"

#define TAG "MY_BOARD"

void* create_board() { 
    return new MyBoard();
}

MyBoard::MyBoard() : Board() {

}

#endif 