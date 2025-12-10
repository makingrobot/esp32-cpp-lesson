/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit5-Lesson51：继电器
 */
#include "config.h"
#if APP_LESSON51==1

#ifndef _EXAMPLE_APP_H
#define _EXAMPLE_APP_H

#pragma message("Compile unit5 lesson51 application.")

#include <string>
#include "src/framework/app/application.h"
#include "src/framework/peripheral/sensor.h"

class ExampleApp : public Application {
public:
    ExampleApp();
    
    bool OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) override;

    const std::string& GetAppName() const override { return "Unit5-Lesson51"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
};

#endif //_EXAMPLE_APP_H

#endif 