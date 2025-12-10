/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit3-Lesson31：按键
 */
#include "config.h"
#if APP_LESSON31==1

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new ExampleApp();
}

ExampleApp::ExampleApp() : Application() { 

}

void ExampleApp::OnInit() {
    // do your init.
}

void ExampleApp::OnLoop() {

    MyBoard *board = static_cast<MyBoard*>(&Board::GetInstance());
    board->ButtonTick();

    delay(1);
}

bool ExampleApp::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {

    if (button_name == kManualButton) {
        Led *led = Board::GetInstance().GetLed();
        if (action == ButtonAction::Click) {
            led->TurnOn();
            delay(1000);
            led->TurnOff();
            delay(1000);

        } else if (action == ButtonAction::DoubleClick) {
            for (int i=0; i<3; i++) {
                led->TurnOn();
                delay(1000);
                led->TurnOff();
                delay(1000);
            }
        }

        return true;
    }

    return Application::OnPhysicalButtonEvent(button_name, action);
}

#endif 