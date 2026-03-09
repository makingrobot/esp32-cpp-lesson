/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "i2s_output.h"
#include "../../sys/log.h"

#define TAG "I2sOutput"

I2sOutput::~I2sOutput() {
    if (tx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_disable(tx_handle_));
    }
}

I2sOutput::I2sOutput(const i2s_chan_config_t& chan_cfg, const i2s_std_config_t& std_cfg) {

    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle_, nullptr));

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle_, &std_cfg));

    Log::Info(TAG, "Simplex channels created");
}

int I2sOutput::Write(const int16_t* data, int samples) {
    
    return 0;
}

#endif //CONFIG_USE_AUDIO