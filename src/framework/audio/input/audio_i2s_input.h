/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_INPUT_H
#define _AUDIO_I2S_INPUT_H

#include <driver/gpio.h>
#include <driver/i2s_std.h>
#include "../audio_input.h"

/**
 * I2s设备输入
 */
class AudioI2sInput : public AudioInput {
private:
    uint32_t Read(void *data, uint32_t len) override;

    i2s_chan_handle_t rx_handle_ = nullptr;

public:
    AudioI2sInput(const i2s_chan_config_t &chan_cfg, const i2s_std_config_t &std_cfg);

    virtual ~AudioI2sInput();
};

#endif // _AUDIO_I2S_INPUT_H

#endif //CONFIG_USE_AUDIO