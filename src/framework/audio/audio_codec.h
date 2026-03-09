/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_CODEC_H
#define _AUDIO_CODEC_H

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <driver/i2s_std.h>
#include <driver/gpio.h>

#include <vector>
#include <string>
#include <functional>

#include "audio_input.h"
#include "audio_output.h"

#define AUDIO_CODEC_DMA_DESC_NUM 6
#define AUDIO_CODEC_DMA_FRAME_NUM 240
#define AUDIO_CODEC_DEFAULT_MIC_GAIN 30.0

class AudioCodec {
public:
    AudioCodec() { }
    virtual ~AudioCodec() { }
    
    virtual void SetOutputVolume(int volume);

    virtual void Start();

    virtual const AudioInput* GetAudioInput() { return nullptr; }
    virtual const AudioOutput* GetAudioOutput() { return nullptr; }

    const int output_volume() const { return output_volume_; }
    
protected:
    int output_volume_ = 70;
    
};

#endif // _AUDIO_CODEC_H

#endif //CONFIG_USE_AUDIO