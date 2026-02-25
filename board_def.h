/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _BOARD_DEF_H
#define _BOARD_DEF_H

#include "config.h"

#if BOARD_LESSON13 == 1
#define BOARD_NAME "lesson13-board"
#include "src/lessons/unit1-lesson13/my_board.h"

#elif BOARD_LESSON21_A == 1
#define BOARD_NAME "lesson21-board"
#include "src/lessons/unit2-lesson21a/my_board.h"

#elif BOARD_LESSON21_B == 1
#define BOARD_NAME "lesson21-board"
#include "src/lessons/unit2-lesson21b/my_board.h"

#elif BOARD_LESSON22_A == 1
#define BOARD_NAME "lesson22-board"
#include "src/lessons/unit2-lesson22a/my_board.h"

#elif BOARD_LESSON22_B == 1
#define BOARD_NAME "lesson22-board"
#include "src/lessons/unit2-lesson22b/my_board.h"

#elif BOARD_LESSON31 == 1
#define BOARD_NAME "lesson31-board"
#include "src/lessons/unit3-lesson31/my_board.h"

#elif BOARD_LESSON32_A == 1
#define BOARD_NAME "lesson32a-board"
#include "src/lessons/unit3-lesson32a/my_board.h"

#elif BOARD_LESSON32_B == 1
#define BOARD_NAME "lesson32b-board"
#include "src/lessons/unit3-lesson32b/my_board.h"

#elif BOARD_LESSON41 == 1
#define BOARD_NAME "lesson41-board"
#include "src/lessons/unit4-lesson41/my_board.h"

#elif BOARD_LESSON42_A == 1
#define BOARD_NAME "lesson42-board"
#include "src/lessons/unit4-lesson42a/my_board.h"

#elif BOARD_LESSON42_B == 1
#define BOARD_NAME "lesson42-board"
#include "src/lessons/unit4-lesson42b/my_board.h"

#elif BOARD_LESSON43 == 1
#define BOARD_NAME "lesson43-board"
#include "src/lessons/unit4-lesson43/my_board.h"

#elif BOARD_LESSON51 == 1
#define BOARD_NAME "lesson51-board"
#include "src/lessons/unit5-lesson51/my_board.h"

#elif BOARD_LESSON52 == 1
#define BOARD_NAME "lesson52-board"
#include "src/lessons/unit5-lesson52/my_board.h"

#elif BOARD_LESSON61_A == 1
#define BOARD_NAME "lesson61a-board"
#include "src/lessons/unit6-lesson61a/my_board.h"

#elif BOARD_LESSON61_B == 1
#define BOARD_NAME "lesson61b-board"
#include "src/lessons/unit6-lesson61b/my_board.h"

#elif BOARD_LESSON62 == 1
#define BOARD_NAME "lesson62-board"
#include "src/lessons/unit6-lesson62/my_board.h"

#elif BOARD_LESSON63_A == 1
#define BOARD_NAME "lesson63a-board"
#include "src/lessons/unit6-lesson63a/my_board.h"

#elif BOARD_LESSON63_B == 1
#define BOARD_NAME "lesson63b-board"
#include "src/lessons/unit6-lesson63b/my_board.h"

#elif BOARD_LESSON63_C == 1
#define BOARD_NAME "lesson63c-board"
#include "src/lessons/unit6-lesson63c/my_board.h"

#elif BOARD_LESSON64_A == 1
#define BOARD_NAME "lesson64-board"
#include "src/lessons/unit6-lesson64a/my_board.h"

#elif BOARD_LESSON64_B == 1
#define BOARD_NAME "lesson64-board"
#include "src/lessons/unit6-lesson64b/my_board.h"

#elif BOARD_LESSON71 == 1
#define BOARD_NAME "lesson71-board"
#include "src/lessons/unit7-lesson71/my_board.h"

#elif BOARD_LESSON72 == 1
#define BOARD_NAME "lesson72-board"
#include "src/lessons/unit7-lesson72/my_board.h"

#elif BOARD_LESSON73 == 1
#define BOARD_NAME "lesson73-board"
#include "src/lessons/unit7-lesson73/my_board.h"
#endif


#endif //_BOARD_DEF_H