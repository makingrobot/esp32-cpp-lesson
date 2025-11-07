
#include <driver/gpio.h>
#include <functional>
#include <Ticker.h>

/**
 * 模拟传感器类
 * 使用 Arduino-ESP32 的 AnalogRead 函数取值。
 */
class AnalogSensor {
public:
    AnalogSensor(gpio_num_t pin);
    virtual ~AnalogSensor();

    void OnNewData(std::function<void(int)> callback) { on_newdata_callback_ = callback; }
    void Start(uint32_t interval);
    void Stop();

    void ReadData();

private:
    gpio_num_t sensor_pin_;
    int sensor_val_;
    Ticker* sensor_ticker_;
    std::function<void(int)> on_newdata_callback_;


};