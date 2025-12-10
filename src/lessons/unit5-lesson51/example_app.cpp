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

#include "example_app.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/peripheral/actuator.h"
#include "src/framework/peripheral/switch_actuator.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new ExampleApp();
}

ExampleApp::ExampleApp() : Application() { 

}

void ExampleApp::OnInit() {
    
}

void ExampleApp::OnLoop() {

    MyBoard *board = static_cast<MyBoard*>(&Board::GetInstance());
    board->ButtonTick();
    
    delay(1);
}

bool ExampleApp::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {

    if (button_name == kManualButton) {

        std::shared_ptr<Actuator> act_ptr = Board::GetInstance().GetActuator(kRelay);
        std::shared_ptr<SwitchActuator> relay_ptr = std::static_pointer_cast<SwitchActuator>(act_ptr);
        if (action == ButtonAction::Click) {
            relay_ptr->Switch();
            return true;
        }
    }

    return Application::OnPhysicalButtonEvent(button_name, action);
}

#endif 