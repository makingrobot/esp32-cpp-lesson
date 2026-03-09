/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit8-Lesson83：在网页上控制设备
 */
#include "config.h"
#if APP_LESSON83==1

#ifndef _HTML_CONTENT_H
#define _HTML_CONTENT_H

static const char *index_html PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
    <title>LED控制</title>
    <meta charset='utf-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'>
</head>
<body>
    <div class='container'>
            LED灯
        <form id="form" action="submit">
            <select name="state" onchange="this.form.submit();">
                <option value="0">关</option>
                <option value="1">开</option>
            </select>
        </form>
    </div>
    
</body>
</html>
)";

#endif //_HTML_CONTENT_H

#endif 