/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_CODEC_H
#define _AUDIO_I2S_CODEC_H

#include <driver/i2s_std.h>
#include <driver/gpio.h>
#include "../audio_codec.h"

#define AUDIO_CODEC_DMA_DESC_NUM 6
#define AUDIO_CODEC_DMA_FRAME_NUM 240
#define AUDIO_CODEC_DEFAULT_MIC_GAIN 30.0

class AudioI2sCodec : public AudioCodec {
public:
    virtual void Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) = 0;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) = 0;
    
    void SetOutputVolume(int volume) override ;

    i2s_data_bit_width_t GetDataBitWidth(int bit_per_sample) 
    {
        if (bit_per_sample == 32) return I2S_DATA_BIT_WIDTH_32BIT;
        else if (bit_per_sample == 24) return I2S_DATA_BIT_WIDTH_24BIT;
        else return I2S_DATA_BIT_WIDTH_16BIT;
    }

protected:
    int channels_;
    int input_sample_rate_;
    int output_sample_rate_;
    int bit_per_sample_;

    bool duplex_ = false;
    
};

#endif // _AUDIO_I2S_CODEC_H

#endif //CONFIG_USE_AUDIO