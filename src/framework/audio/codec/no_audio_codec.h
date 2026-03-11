/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _NO_AUDIO_CODEC_H
#define _NO_AUDIO_CODEC_H

#include "../audio_codec.h"

#include <driver/gpio.h>
#include <driver/i2s_pdm.h>

class NoAudioCodec : public AudioCodec {
private:
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

public:
    virtual ~NoAudioCodec();

};

/**
 * 分立的I2S设备
 */
class NoAudioCodecSimplex : public NoAudioCodec {
public:
    // speaker
    NoAudioCodecSimplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout)
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout) { }

    // speaker + mic
    NoAudioCodecSimplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, 
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
class NoAudioCodecSimplexMic : public NoAudioCodec {
public:
    // mic
    NoAudioCodecSimplexMic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din) 
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
class NoAudioCodecSimplexPdm : public NoAudioCodec {
public:
    NoAudioCodecSimplexPdm(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck,  gpio_num_t mic_din)
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
class NoAudioCodecDuplex : public NoAudioCodec {
public:
    NoAudioCodecDuplex(gpio_num_t bclk, gpio_num_t ws, gpio_num_t dout, gpio_num_t din)
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

#endif // _NO_AUDIO_CODEC_H

#endif //CONFIG_USE_AUDIO