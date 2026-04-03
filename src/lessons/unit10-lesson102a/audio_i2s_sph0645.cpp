#include "config.h"
#if BOARD_LESSON102_A == 1

#include "audio_i2s_sph0645.h"

#include "src/framework/sys/log.h"

#define TAG "AudioI2sSph0645"

AudioI2sSph0645::AudioI2sSph0645(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, gpio_num_t mclk) 
{  
    i2s_driver_ = new I2sDriver();
    i2s_driver_->setPins(mic_sck, mic_ws, -1, mic_din, mclk);
}

bool AudioI2sSph0645::Init(const audio_config_t &config)
{
    Log::Info(TAG, "Init...");
    AudioI2sCodec::Init(config);
    
    uint32_t sample_rate = 16000;

    if (!i2s_driver_->begin(I2S_MODE_STD, sample_rate, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT)) {
        Log::Error(TAG, "Failed to initialize I2S!");
        return false;
    }

    // 对于SPH0645LM4H型号的麦克风，配置一个32bit->16bit的转换程序
    i2s_driver_->configureRX(sample_rate, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO, I2S_RX_TRANSFORM_32_TO_16);

    Log::Info(TAG, "i2s initialize success.");
    return true;
}

audio_config_t AudioI2sSph0645::audio_config() 
{
    audio_config_t cfg = {
        .input_rate = (sample_rate_t)16000,
        .input_bits = (sample_bits_t)32,
        .input_channels = (channels_t)1,
        .output_rate = (sample_rate_t)i2s_driver_->rxSampleRate(),
        .output_bits = (sample_bits_t)i2s_driver_->rxDataWidth(),
        .output_channels = (channels_t)i2s_driver_->rxSlotMode()
    };
    return cfg;
}

#endif