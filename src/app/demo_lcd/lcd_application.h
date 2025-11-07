/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_LCD==1

#ifndef _LCD_APPLICATION_H
#define _LCD_APPLICATION_H

#include "../application.h"

class LcdApplication : public Application {
public:
    LcdApplication();
    ~LcdApplication();
    
    void Init() override;
    void Start() override;

private:

};

#endif //_LCD_APPLICATION_H

#endif //APP_DEMO_LCD