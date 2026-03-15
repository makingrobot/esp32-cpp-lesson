/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_SIMPLE_H
#define _AUDIO_I2S_SIMPLE_H

#include <driver/gpio.h>
#include "audio_i2s_codec.h"
#include "../../board/i2s_driver.h"

class AudioI2sSimple : public AudioI2sCodec {
public:
    virtual ~AudioI2sSimple();

    virtual bool Init(int sample_rate, int bit_per_sample, int channel) override;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

protected:
    I2sDriver *tx_driver_ = nullptr;
    I2sDriver *rx_driver_ = nullptr;
    I2sDriver *duplex_driver_ = nullptr;
};

/**
 * I2S 喇叭
 */
class AudioI2sSimpleSpeaker : public AudioI2sSimple {
public:
    // speaker
    AudioI2sSimpleSpeaker(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout)
    { 
        tx_driver_ = new I2sDriver();
        tx_driver_->setPins(spk_bclk, spk_ws, spk_dout);
    }

private:

};

/**
 * I2S 麦克风设备
 */
class AudioI2sSimpleMic : public AudioI2sSimple {
public:
    // mic
    AudioI2sSimpleMic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din) 
    {  
        rx_driver_ = new I2sDriver();
        rx_driver_->setPins(mic_sck, mic_ws, -1, mic_din);
    }

private:

};

/**
 * I2S 喇叭 + 麦
 */
class AudioI2sSimpleDuplex : public AudioI2sSimple {
public:
    // speaker + mic
    AudioI2sSimpleDuplex(gpio_num_t bclk, gpio_num_t ws, gpio_num_t dout, gpio_num_t din, gpio_num_t mclk=GPIO_NUM_NC)
    { 
        duplex_driver_ = new I2sDriver();
        duplex_driver_->setPins(bclk, ws, dout, din, mclk);
    }

private:

};

#endif // _AUDIO_I2S_NO_CODEC_H

#endif //CONFIG_USE_AUDIO