/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_NO_CODEC_H
#define _AUDIO_I2S_NO_CODEC_H

#include "audio_i2s_codec.h"

#include <driver/gpio.h>

class AudioI2sNoCodec : public AudioI2sCodec {
public:
    virtual ~AudioI2sNoCodec();

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;

    enum : int { APLL_AUTO = -1, APLL_ENABLE = 1, APLL_DISABLE = 0 };

protected:
    void MakeSampleStereo16(int16_t sample[2]) {
        // Mono to "stereo" conversion
        if (channels_ == 1)
            sample[1] = sample[0];
        if (bit_per_sample_ == 8) {
            // Upsample from unsigned 8 bits to signed 16 bits
            sample[0] = (((int16_t)(sample[0]&0xff)) - 128) << 8;
            sample[1] = (((int16_t)(sample[1]&0xff)) - 128) << 8;
        }
    };

    inline int16_t Amplify(int16_t s) {
        int32_t v = (s * gainF2P6)>>6;
        if (v < -32767) return -32767;
        else if (v > 32767) return 32767;
        else return (int16_t)(v&0xffff);
    }

    bool SetGain(float f) { 
        if (f>4.0) f=4.0; 
        if (f<0.0) f=0.0; 
        gainF2P6 = (uint8_t)(f*(1<<6)); 
        return true; 
    }

    bool mono_ = false;
    int dma_buf_count_;
    int use_apll_;
    uint8_t gainF2P6; // Fixed point 2.6
};

/**
 * 分立的I2S设备
 */
class AudioI2sNoCodecSimplex : public AudioI2sNoCodec {
public:
    // speaker
    AudioI2sNoCodecSimplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, 
            int dma_buf_count = 8, int use_apll=APLL_DISABLE)
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout) 
    { 
        dma_buf_count_ = dma_buf_count;
        use_apll_ = use_apll;
        SetGain(1.0);
    }

    // speaker + mic
    AudioI2sNoCodecSimplex(gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, 
            gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, 
            int dma_buf_count = 8, int use_apll=APLL_DISABLE) 
        : spk_bclk_(spk_bclk), spk_ws_(spk_ws), spk_dout_(spk_dout), mic_sck_(mic_sck), mic_ws_(mic_ws), mic_din_(mic_din)
    { 
        dma_buf_count_ = dma_buf_count;
        use_apll_ = use_apll;
        duplex_ = true; 
        SetGain(1.0);
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
class AudioI2sNoCodecSimplexMic : public AudioI2sNoCodec {
public:
    // mic
    AudioI2sNoCodecSimplexMic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din,
            int dma_buf_count = 8, int use_apll=APLL_DISABLE) 
        : mic_sck_(mic_sck), mic_ws_(mic_ws), mic_din_(mic_din)
    {  
        dma_buf_count_ = dma_buf_count;
        use_apll_ = use_apll;
        SetGain(1.0);
    }

    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;

private:
    gpio_num_t mic_sck_;
    gpio_num_t mic_ws_;
    gpio_num_t mic_din_;
};

#endif // _AUDIO_I2S_NO_CODEC_H

#endif //CONFIG_USE_AUDIO