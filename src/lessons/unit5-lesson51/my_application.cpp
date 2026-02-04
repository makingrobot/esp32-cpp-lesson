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

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/peripheral/actuator.h"
#include "src/framework/peripheral/switch_actuator.h"
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
    MyBoard *board = static_cast<MyBoard*>(&Board::GetInstance());
    board->ButtonTick();
    
    delay(1);
}

bool MyApplication::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {
    if (button_name == kManualButton) {
        Board& board = Board::GetInstance();
        std::shared_ptr<Actuator> act_ptr = board.GetActuator(kRelay);
        std::shared_ptr<SwitchActuator> relay_ptr = std::static_pointer_cast<SwitchActuator>(act_ptr);
        if (action == ButtonAction::Click) {
            relay_ptr->Switch();
            if (relay_ptr->IsOn()) {
                board.GetLed()->TurnOn();
            } else {
                board.GetLed()->TurnOff();
            }
            return true;
        }
    }

    return Application::OnPhysicalButtonEvent(button_name, action);
}

#endif 