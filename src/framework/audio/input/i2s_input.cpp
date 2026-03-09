/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "i2s_input.h"
#include "../../sys/log.h"

#define TAG "I2sInput"

I2sInput::~I2sInput() {
    if (rx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_disable(rx_handle_));
    }
}

I2sInput::I2sInput(const i2s_chan_config_t &chan_cfg, const i2s_std_config_t &std_cfg) {

    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, nullptr, &rx_handle_));

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle_, &std_cfg));

    Log::Info(TAG, "Simplex channels created");
}

int I2sInput::Read(int16_t* dest, int samples) {
    
    return 0;
}

#endif //CONFIG_USE_AUDIO