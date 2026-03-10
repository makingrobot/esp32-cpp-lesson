/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_input.h"
#include "../../sys/log.h"

#define TAG "I2sInput"

AudioI2sInput::~AudioI2sInput() {
    if (rx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_disable(rx_handle_));
    }
}

AudioI2sInput::AudioI2sInput(const i2s_chan_config_t &chan_cfg, const i2s_std_config_t &std_cfg) {

    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, nullptr, &rx_handle_));

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle_, &std_cfg));

    Log::Info(TAG, "Simplex channels created");
}

uint32_t AudioI2sInput::Read(void *data, uint32_t len) {
    
    return 0;
}

#endif //CONFIG_USE_AUDIO