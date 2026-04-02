#include "config.h"
#if BOARD_LESSON102_A == 1

#include "audio_i2s_sph0645.h"

#include "src/framework/sys/log.h"

#define TAG "AudioI2sSph0645"

bool AudioI2sSph0645::Init(const audio_config_t &config)
{
    Log::Info(TAG, "Init...");
    AudioI2sCodec::Init(config);
    
    uint32_t sample_rate = 16000;

    if (!i2s_driver_->begin(I2S_MODE_STD, sample_rate, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT)) {
        Log::Error(TAG, "Failed to initialize I2S!");
        return false;
    }

    // Resample the 32bit SPH0645 microphone data into 16bit. SPH0645 is actually 18 bit
    i2s_driver_->configureRX(sample_rate, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO, I2S_RX_TRANSFORM_32_TO_16);

    Log::Info(TAG, "i2s initialize success.");
    return true;
}

audio_config_t AudioI2sSph0645::audio_config() 
{
    audio_config_t cfg = {
        .rate = (sample_rate_t)i2s_driver_->rxSampleRate(),
        .bits = (sample_bits_t)i2s_driver_->rxDataWidth(),
        .channels = (channels_t)i2s_driver_->rxSlotMode()
    };
    return cfg;
}

#endif