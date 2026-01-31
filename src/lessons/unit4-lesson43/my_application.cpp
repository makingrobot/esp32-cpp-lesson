/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson44：红外遥控
 */
#include "config.h"
#if APP_LESSON43==1

#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "my_board.h"

#define TAG "ExampleApp"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    // 启动传感器收集数据
    std::shared_ptr<Sensor> irsensor_ptr = Board::GetInstance().GetSensor(kIrSensor);
    irsensor_ptr->Start(100);
}

void MyApplication::OnLoop() {
    Led *led = Board::GetInstance().GetLed();

    switch (ir_code_) {
        case 0xF30CFF00:  // 遥控器上“1”键
            led->TurnOn();
            break;

        case 0xE718FF00:
            led->TurnOff();  // 遥控器上“2”键
            break;
    }

    delay(100);
}

bool MyApplication::OnSensorDataEvent(const std::string& sensor_name, const SensorValue& value) {
    // 处理传感器数据
    if (sensor_name == kIrSensor) {
        
        Log::Info(TAG, "ir code: %02X", value.ulongValue());
        ir_code_ = value.ulongValue();
        return true;
    }

    return Application::OnSensorDataEvent(sensor_name, value);
}

#endif 