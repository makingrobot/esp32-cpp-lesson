/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_INPUT_H
#define _AUDIO_I2S_INPUT_H

#include "../audio_codec.h"
#include "../audio_input.h"

/**
 * I2s设备输入
 */
class AudioI2sInput : public AudioInput {
public:
    AudioI2sInput(AudioCodec *codec) : codec_(codec) {  }
    virtual ~AudioI2sInput() {  }

    virtual bool Init() override;
    virtual sample_data_t Handle() override;
    virtual bool Close() override;
    virtual bool isEOF() override;

    virtual const char* Tag() override { return "I2sInput"; };
    virtual audio_config_t audio_config() override 
    {
        return codec_->input_config();
    }

private:
    AudioCodec *codec_;
    int16_t samples_[128];
    const uint32_t samples_len_ = 128;
};

#endif // _AUDIO_I2S_INPUT_H

#endif //CONFIG_USE_AUDIO