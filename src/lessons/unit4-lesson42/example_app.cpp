/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson43：旋转电位器
 */
#include "config.h"
#if APP_LESSON42==1

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
    Log::Info(TAG, "Initial.");

    // 启动传感器收集数据
    std::shared_ptr<Sensor> sensor_ptr = Board::GetInstance().GetSensor(kPotentiometer);
    sensor_ptr->Start(100);
}

void ExampleApp::OnLoop() {

    delay(1);
}

bool ExampleApp::OnSensorDataEvent(const std::string& sensor_name, const SensorValue& value) {
    
    // 步骤三：处理传感器数据
    if (sensor_name == kPotentiometer) {
        // 电位器的值范围为：0-4095，一般使用map函数进行转换
        int new_value = map(value.intValue(), 0, 4095, 0, 99);
        if (new_value != prev_value_) {
            Log::Info(TAG, "new value: %d", new_value);
            prev_value_ = new_value;
        }
        return true;
    }

    return Application::OnSensorDataEvent(sensor_name, value);
}

#endif 