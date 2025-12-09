/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#ifndef _CONFIG_H
#define _CONFIG_H

#define APP_LESSON43        1

/********** Unit1 **********/
#if APP_LESSON01 == 1
#define BOARD_LESSON01      1
#include "src/lessons/unit1-lesson01/app_config.h"
#include "src/lessons/unit1-lesson01/board_config.h"

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

#endif

#endif //_CONFIG_H