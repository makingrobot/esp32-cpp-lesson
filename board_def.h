/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _BOARD_DEF_H
#define _BOARD_DEF_H

#include "config.h"

#if BOARD_LESSON01 == 1
#define BOARD_NAME "lesson01-board"
#include "src/lessons/unit1-lesson01/my_board.h"

#elif BOARD_LESSON21 == 1
#define BOARD_NAME "lesson21-board"
#include "src/lessons/unit2-lesson21/my_board.h"

#elif BOARD_LESSON22 == 1
#define BOARD_NAME "lesson22-board"
#include "src/lessons/unit2-lesson22/my_board.h"

#elif BOARD_LESSON23 == 1
#define BOARD_NAME "lesson23-board"
#include "src/lessons/unit2-lesson23/my_board.h"

#elif BOARD_LESSON31 == 1
#define BOARD_NAME "lesson31-board"
#include "src/lessons/unit3-lesson31/my_board.h"

#elif BOARD_LESSON32 == 1
#define BOARD_NAME "lesson32-board"
#include "src/lessons/unit3-lesson32/my_board.h"

#elif BOARD_LESSON33 == 1
#define BOARD_NAME "lesson33-board"
#include "src/lessons/unit3-lesson33/my_board.h"

#elif BOARD_LESSON41 == 1
#define BOARD_NAME "lesson41-board"
#include "src/lessons/unit4-lesson41/my_board.h"

#elif BOARD_LESSON42 == 1
#define BOARD_NAME "lesson42-board"
#include "src/lessons/unit4-lesson42/my_board.h"

#elif BOARD_LESSON43 == 1
#define BOARD_NAME "lesson43-board"
#include "src/lessons/unit4-lesson43/my_board.h"

#endif


#endif //_BOARD_DEF_H