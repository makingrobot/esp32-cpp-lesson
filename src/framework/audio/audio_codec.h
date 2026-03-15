/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_CODEC_H
#define _AUDIO_CODEC_H

class AudioCodec {
public:
    virtual bool Init(int sample_rate, int bit_per_sample, int channel) = 0;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) = 0;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) = 0;
    
    virtual void SetOutputVolume(int volume) = 0;
    const int output_volume() const { return output_volume_; }

protected:
    int output_volume_;

};

#endif // _AUDIO_CODEC_H

#endif //CONFIG_USE_AUDIO