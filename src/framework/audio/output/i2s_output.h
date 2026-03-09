/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _I2S_OUTPUT_H
#define _I2S_OUTPUT_H

#include <driver/gpio.h>
#include <driver/i2s_std.h>
#include "../audio_output.h"

/**
 * I2s设备输出
 */
class I2sOutput : public AudioOutput {
public:
    I2sOutput(const i2s_chan_config_t& chan_cfg, const i2s_std_config_t& std_cfg);
    virtual ~I2sOutput();

private:
    int Write(const int16_t* data, int samples);
    
    i2s_chan_handle_t tx_handle_ = nullptr;
    int output_sample_rate_;

};

#endif // _I2S_OUTPUT_H

#endif