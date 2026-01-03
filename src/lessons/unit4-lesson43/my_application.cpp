/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit4-Lesson43：温湿度传感器
 */
#include "config.h"
#if APP_LESSON43==1

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
    
    // 步骤二：启动传感器收集数据
    std::shared_ptr<Sensor> dht11_ptr = Board::GetInstance().GetSensor(kDht11);
    if (dht11_ptr!=nullptr) {
        dht11_ptr->Start(180000);
    }
}

void MyApplication::OnLoop() {

    delay(1);
}

bool MyApplication::OnSensorDataEvent(const std::string& sensor_name, const SensorValue& value) {
    
    // 步骤三：处理传感器数据
    if (sensor_name == kDht11) {
        float weidu = value.floatList().at(0);
        float shidu = value.floatList().at(1);
        Log::Info(TAG, "温度：%.1f, 湿度：%.1f", weidu, shidu);
        return true;
    }

    return Application::OnSensorDataEvent(sensor_name, value);
}

#endif 