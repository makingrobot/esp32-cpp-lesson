/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_SIMPLEX_H
#define _AUDIO_I2S_SIMPLEX_H

#include <driver/gpio.h>
#include "audio_i2s_codec.h"
#include "../../board/i2s_driver.h"

/**
 * 单工 I2S
 */
class AudioI2sSimplex : public AudioI2sCodec {
public:
    virtual ~AudioI2sSimplex();

    virtual bool Init(const audio_config_t &config) override;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

protected:
    I2sDriver *i2s_driver_ = nullptr;
    bool input_enable_ = false;
    bool output_enable_ = false;
};

/**
 * I2S 喇叭
 */
class AudioI2sSimplexSpeaker : public AudioI2sSimplex {
public:
    // speaker
    AudioI2sSimplexSpeaker(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mclk=GPIO_NUM_NC)
    { 
        i2s_driver_ = new I2sDriver();
        i2s_driver_->setPins(spk_bclk, spk_ws, spk_dout, -1, mclk);
        output_enable_ = true;
    }

private:

};

/**
 * I2S 麦克风设备
 */
class AudioI2sSimplexMic : public AudioI2sSimplex {
public:
    // mic
    AudioI2sSimplexMic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, gpio_num_t mclk=GPIO_NUM_NC) 
    {  
        i2s_driver_ = new I2sDriver();
        i2s_driver_->setPins(mic_sck, mic_ws, -1, mic_din, mclk);
        input_enable_ = true;
    }

private:

};

#endif // _AUDIO_I2S_SIMPLEX_H

#endif //CONFIG_USE_AUDIO