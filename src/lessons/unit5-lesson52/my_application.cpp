/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit5-Lesson51：舵机控制
 */
#include "config.h"
#if APP_LESSON52==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/peripheral/servo_driver.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    std::shared_ptr<Actuator> act_ptr = Board::GetInstance().GetActuator(kSG90);
    std::shared_ptr<ServoDriver> servo_ptr = std::static_pointer_cast<ServoDriver>(act_ptr);
    servo_ptr->Reset();
}

void MyApplication::OnLoop() {
    MyBoard *board = (MyBoard*)(&Board::GetInstance());
    board->ButtonTick();
    
    delay(1);
}

bool MyApplication::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {
    if (button_name == kManualButton) {
        if (action == ButtonAction::Click) {
            StepMove(5);
            return true;

        } else if (action == ButtonAction::DoubleClick) {
            StepMove(-5);
            return true;
        }
    }

    return Application::OnPhysicalButtonEvent(button_name, action);
}

void MyApplication::StepMove(int step) {
    std::shared_ptr<Actuator> act_ptr = Board::GetInstance().GetActuator(kSG90);
    std::shared_ptr<ServoDriver> servo_ptr = std::static_pointer_cast<ServoDriver>(act_ptr);
    Schedule([servo_ptr, step](){
        servo_ptr->Move(step);
    });
}

#endif 