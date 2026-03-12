/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_codec.h"
#include <cstring>
#include <driver/i2s_common.h>

#include "../../sys/log.h"
#include "../../sys/settings.h"

#define TAG "AudioI2sCodec"

void AudioI2sCodec::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample)
{
    input_sample_rate_ = input_sample_rate;
    output_sample_rate_ = output_sample_rate;
    bit_per_sample_ = bit_per_sample;
    
    Settings settings("audio", false);
    output_volume_ = settings.GetInt("output_volume", output_volume_);
    if (output_volume_ <= 0) {
        Log::Warn(TAG, "Output volume value (%d) is too small, setting to default (10)", output_volume_);
        output_volume_ = 10;
    }
}

void AudioI2sCodec::SetOutputVolume(int volume) {
    output_volume_ = volume;
    Log::Info(TAG, "Set output volume to %d", output_volume_);
    
    Settings settings("audio", true);
    settings.SetInt("output_volume", output_volume_);
}

#endif //CONFIG_USE_AUDIO