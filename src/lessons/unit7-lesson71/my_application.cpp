/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit6-Lesson71：四段7位数码管
 */
#include "config.h"
#if APP_LESSON71==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    
}

void MyApplication::OnLoop() {
    MyBoard *board = (MyBoard *)(&Board::GetInstance());
    TM1650 *d = board->GetTM1650();

    d->displayOff();
    d->displayString("____");
    d->setBrightness(TM1650_MIN_BRIGHT);
    d->displayOn();
    delay(100);

    char line[] = "1234";
    d->displayString(line);
    d->setBrightnessGradually(TM1650_MAX_BRIGHT);
    delay(2000);

    d->setBrightnessGradually(TM1650_MIN_BRIGHT);
    d->displayOff();
    delay(1000);
    
    line[1] |= 128;
    d->displayOn();
    d->setBrightnessGradually(TM1650_MAX_BRIGHT);
    d->displayString(line);
    delay(2000);
    
    d->displayString("abcd");
    delay(2000);

    d->displayString("789 ");
    delay(2000);
    
    if (d->displayRunning("1234567890abcdef")) {
        while (d->displayRunningShift()) delay(500);
    }
    delay(2000);
    
    for (int i = 0; i<20; i++) {
        d->displayOff();
        delay(200);

        d->displayOn();
        delay(200);
    }
    
    for (int i = 0; i<20; i++) {
        d->setBrightness(1);
        delay(200);

        d->setBrightness(7);
        delay(200);
    }

    for (int i = 0; i<20; i++) {
        for (int j = 0; j<4; j++) {
            d->setDot(j,true);
            delay(200);
        }
        for (int j = 0; j<4; j++) {
            d->setDot(j,false);
            delay(200);
        }
    }
}

#endif 