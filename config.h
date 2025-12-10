/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _CONFIG_H
#define _CONFIG_H

#define APP_LESSON13        1

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
#elif APP_LESSON21 == 1
#define BOARD_LESSON21      1
#include "src/lessons/unit2-lesson21/app_config.h"
#include "src/lessons/unit2-lesson21/board_config.h"

#elif APP_LESSON22 == 1
#define BOARD_LESSON22      1
#include "src/lessons/unit2-lesson22/app_config.h"
#include "src/lessons/unit2-lesson22/board_config.h"

#elif APP_LESSON23 == 1
#define BOARD_LESSON23      1
#include "src/lessons/unit2-lesson23/app_config.h"
#include "src/lessons/unit2-lesson23/board_config.h"

/********** Unit3 **********/
#elif APP_LESSON31 == 1
#define BOARD_LESSON31      1
#include "src/lessons/unit3-lesson31/app_config.h"
#include "src/lessons/unit3-lesson31/board_config.h"

#elif APP_LESSON32 == 1
#define BOARD_LESSON32      1
#include "src/lessons/unit3-lesson32/app_config.h"
#include "src/lessons/unit3-lesson32/board_config.h"

#elif APP_LESSON33 == 1
#define BOARD_LESSON33      1
#include "src/lessons/unit3-lesson33/app_config.h"
#include "src/lessons/unit3-lesson33/board_config.h"

/********** Unit4 **********/
#elif APP_LESSON41 == 1
#define BOARD_LESSON41      1
#include "src/lessons/unit4-lesson41/app_config.h"
#include "src/lessons/unit4-lesson41/board_config.h"

#elif APP_LESSON42 == 1
#define BOARD_LESSON42      1
#include "src/lessons/unit4-lesson42/app_config.h"
#include "src/lessons/unit4-lesson42/board_config.h"

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
#elif APP_LESSON61 == 1
#define BOARD_LESSON61      1
#include "src/lessons/unit6-lesson61/app_config.h"
#include "src/lessons/unit6-lesson61/board_config.h"

#elif APP_LESSON62 == 1
#define BOARD_LESSON62      1
#include "src/lessons/unit6-lesson62/app_config.h"
#include "src/lessons/unit6-lesson62/board_config.h"

#elif APP_LESSON63 == 1
#define BOARD_LESSON63      1
#include "src/lessons/unit6-lesson63/app_config.h"
#include "src/lessons/unit6-lesson63/board_config.h"

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