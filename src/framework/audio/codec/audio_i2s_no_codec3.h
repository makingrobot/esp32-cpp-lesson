/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_NO_CODEC3_H
#define _AUDIO_I2S_NO_CODEC3_H

#include "audio_i2s_codec.h"

#include <driver/gpio.h>
#include <driver/i2s_pdm.h>

class AudioI2sNoCodec3 : public AudioI2sCodec {
public:
    virtual ~AudioI2sNoCodec3();

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

protected:
    i2s_chan_handle_t tx_handle_ = nullptr;
    i2s_chan_handle_t rx_handle_ = nullptr;

};

/**
 * 分立的I2S设备
 */
class AudioI2sNoCodec3Simplex : public AudioI2sNoCodec3 {
public:
    // speaker
    AudioI2sNoCodec3Simplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout)
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout) { }

    // speaker + mic
    AudioI2sNoCodec3Simplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, 
        gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din) 
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout), mic_sck_(mic_sck), mic_ws_(mic_ws), mic_din_(mic_din)
    { 
        duplex_ = true; 
    }

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;

private:
    gpio_num_t spk_bclk_; 
    gpio_num_t spk_ws_; 
    gpio_num_t spk_dout_;
    gpio_num_t mic_sck_;
    gpio_num_t mic_ws_;
    gpio_num_t mic_din_;
};

/**
 * I2S 麦克风设备
 */
class AudioI2sNoCodec3SimplexMic : public AudioI2sNoCodec3 {
public:
    // mic
    AudioI2sNoCodec3SimplexMic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din) 
        : mic_sck_(mic_sck), mic_ws_(mic_ws), mic_din_(mic_din) {  }

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;

private:
    gpio_num_t mic_sck_;
    gpio_num_t mic_ws_;
    gpio_num_t mic_din_;
};

/**
 * 支持PDM的I2S设备
 */
class AudioI2sNoCodec3SimplexPdm : public AudioI2sNoCodec3 {
public:
    AudioI2sNoCodec3SimplexPdm(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck,  gpio_num_t mic_din)
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout), mic_sck_(mic_sck), mic_din_(mic_din) 
    { 
        duplex_ = true;
    }
    
    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

private:
    gpio_num_t spk_bclk_; 
    gpio_num_t spk_ws_; 
    gpio_num_t spk_dout_; 
    gpio_num_t mic_sck_;  
    gpio_num_t mic_din_;
};

/* 无编解码芯片的双工I2S设备 */
class AudioI2sNoCodec3Duplex : public AudioI2sNoCodec3 {
public:
    AudioI2sNoCodec3Duplex(gpio_num_t bclk, gpio_num_t ws, gpio_num_t dout, gpio_num_t din)
        : bclk_(bclk), ws_(ws), dout_(dout), din_(din) 
    { 
        duplex_ = true; 
    }

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;

private:
    gpio_num_t bclk_;
    gpio_num_t ws_; 
    gpio_num_t dout_; 
    gpio_num_t din_;
};

#endif // _AUDIO_I2S_NO_CODEC3_H

#endif //CONFIG_USE_AUDIO