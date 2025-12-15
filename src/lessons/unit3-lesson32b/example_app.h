/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit3-Lesson33：触摸输入（中断方式）
 */
#include "config.h"
#if APP_LESSON32_B==1

#ifndef _EXAMPLE_APP_H
#define _EXAMPLE_APP_H

#pragma message("Compile unit3 lesson32b application.")

#include <string>
#include "src/framework/app/application.h"

class ExampleApp : public Application {
public:
    ExampleApp();
    
    /**
     * ESP32触摸引脚
     */
    bool OnPinTouchEvent(const std::string& touch_name) override;

    const std::string& GetAppName() const override { return "Unit3-Lesson32b"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    bool touch1_detected_ = false;
};

#endif //_EXAMPLE_APP_H

#endif 