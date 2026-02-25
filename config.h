/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _CONFIG_H
#define _CONFIG_H

#define APP_LESSON63_C        1

/********** Unit1 **********/
#if APP_LESSON11 ==1
#define BOARD_NAME   ""

#elif APP_LESSON12 ==1
#define BOARD_NAME   ""

#elif APP_LESSON13 == 1
#define BOARD_LESSON13      1
#include "src/lessons/unit1-lesson13/app_config.h"
#include "src/lessons/unit1-lesson13/board_config.h"

/********** Unit2 **********/
#elif APP_LESSON21_A == 1
#define BOARD_LESSON21_A     1
#include "src/lessons/unit2-lesson21a/app_config.h"
#include "src/lessons/unit2-lesson21a/board_config.h"

#elif APP_LESSON21_B == 1
#define BOARD_LESSON21_B     1
#include "src/lessons/unit2-lesson21b/app_config.h"
#include "src/lessons/unit2-lesson21b/board_config.h"

#elif APP_LESSON22_A == 1
#define BOARD_LESSON22_A      1
#include "src/lessons/unit2-lesson22a/app_config.h"
#include "src/lessons/unit2-lesson22a/board_config.h"

#elif APP_LESSON22_B == 1
#define BOARD_LESSON22_B      1
#include "src/lessons/unit2-lesson22b/app_config.h"
#include "src/lessons/unit2-lesson22b/board_config.h"

/********** Unit3 **********/
#elif APP_LESSON31 == 1
#define BOARD_LESSON31      1
#include "src/lessons/unit3-lesson31/app_config.h"
#include "src/lessons/unit3-lesson31/board_config.h"

#elif APP_LESSON32_A == 1
#define BOARD_LESSON32_A      1
#include "src/lessons/unit3-lesson32a/app_config.h"
#include "src/lessons/unit3-lesson32a/board_config.h"

#elif APP_LESSON32_B == 1
#define BOARD_LESSON32_B      1
#include "src/lessons/unit3-lesson32b/app_config.h"
#include "src/lessons/unit3-lesson32b/board_config.h"

/********** Unit4 **********/
#elif APP_LESSON41 == 1
#define BOARD_LESSON41      1
#include "src/lessons/unit4-lesson41/app_config.h"
#include "src/lessons/unit4-lesson41/board_config.h"

#elif APP_LESSON42_A == 1
#define BOARD_LESSON42_A      1
#include "src/lessons/unit4-lesson42a/app_config.h"
#include "src/lessons/unit4-lesson42a/board_config.h"

#elif APP_LESSON42_B == 1
#define BOARD_LESSON42_B      1
#include "src/lessons/unit4-lesson42b/app_config.h"
#include "src/lessons/unit4-lesson42b/board_config.h"

#elif APP_LESSON43 == 1
#define BOARD_LESSON43      1
#include "src/lessons/unit4-lesson43/app_config.h"
#include "src/lessons/unit4-lesson43/board_config.h"

/********** Unit5 **********/
#elif APP_LESSON51 == 1
#define BOARD_LESSON51      1
#include "src/lessons/unit5-lesson51/app_config.h"
#include "src/lessons/unit5-lesson51/board_config.h"

#elif APP_LESSON52 == 1
#define BOARD_LESSON52      1
#include "src/lessons/unit5-lesson52/app_config.h"
#include "src/lessons/unit5-lesson52/board_config.h"

/********** Unit6 **********/
#elif APP_LESSON61_A == 1
#define BOARD_LESSON61_A      1
#include "src/lessons/unit6-lesson61a/app_config.h"
#include "src/lessons/unit6-lesson61a/board_config.h"

#elif APP_LESSON61_B == 1
#define BOARD_LESSON61_B      1
#include "src/lessons/unit6-lesson61b/app_config.h"
#include "src/lessons/unit6-lesson61b/board_config.h"

#elif APP_LESSON62 == 1
#define BOARD_LESSON62      1
#include "src/lessons/unit6-lesson62/app_config.h"
#include "src/lessons/unit6-lesson62/board_config.h"

#elif APP_LESSON63_A == 1
#define BOARD_LESSON63_A      1
#include "src/lessons/unit6-lesson63a/app_config.h"
#include "src/lessons/unit6-lesson63a/board_config.h"

#elif APP_LESSON63_B == 1
#define BOARD_LESSON63_B      1
#include "src/lessons/unit6-lesson63b/app_config.h"
#include "src/lessons/unit6-lesson63b/board_config.h"

#elif APP_LESSON63_C == 1
#define BOARD_LESSON63_C      1
#include "src/lessons/unit6-lesson63c/app_config.h"
#include "src/lessons/unit6-lesson63c/board_config.h"

#elif APP_LESSON64_A == 1
#define BOARD_LESSON64_A      1
#include "src/lessons/unit6-lesson64a/app_config.h"
#include "src/lessons/unit6-lesson64a/board_config.h"

#elif APP_LESSON64_B == 1
#define BOARD_LESSON64_B      1
#include "src/lessons/unit6-lesson64b/app_config.h"
#include "src/lessons/unit6-lesson64b/board_config.h"

/********** Unit7 **********/
#elif APP_LESSON71 == 1
#define BOARD_LESSON71      1
#include "src/lessons/unit7-lesson71/app_config.h"
#include "src/lessons/unit7-lesson71/board_config.h"

#elif APP_LESSON72 == 1
#define BOARD_LESSON72      1
#include "src/lessons/unit7-lesson72/app_config.h"
#include "src/lessons/unit7-lesson72/board_config.h"

#elif APP_LESSON63 == 1
#define BOARD_LESSON63      1
#include "src/lessons/unit7-lesson73/app_config.h"
#include "src/lessons/unit7-lesson73/board_config.h"

#endif

#endif //_CONFIG_H