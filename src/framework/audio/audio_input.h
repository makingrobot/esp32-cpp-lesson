/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_INPUT_H
#define _AUDIO_INPUT_H

#include "audio_status.h"

/**
 * 音频输入基类
 */
class AudioInput {
public:
    virtual bool Init() { return false; }

    virtual bool Handle() = 0;
    virtual bool Close() = 0;
    virtual int16_t* GetSamples() = 0;
    virtual bool isEOF() = 0;
    virtual const char* Tag() = 0;
    
    void SetSampleRate(int rate) { sample_rate_ = rate; }
    void SetBitPerSample(int bit) { bit_per_sample_ = bit; }
    void SetChannels(int chn) { channels_ = chn; }

    virtual void SetMetadataCallback(AudioStatus::MetadataCallbackFn fn, void *data) {
        status.RegisterMetadataCallback(fn, Tag(), data);
    }

    virtual void SetStatusCallback(AudioStatus::StatusCallbackFn fn, void *data) { 
        status.RegisterStatusCallback(fn, Tag(), data);
    }

protected:
    int sample_rate_ = 44100;
    int bit_per_sample_ = 16;
    int channels_ = 1;

    AudioStatus status;
    
};

#endif // _AUDIO_INPUT_H

#endif //CONFIG_USE_AUDIO