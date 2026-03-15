/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_simple.h"

#include <cmath>
#include <cstring>
#include <Arduino.h>

#include "../../sys/log.h"

#define TAG "AudioI2sSimple"

bool AudioI2sSimple::Init(int sample_rate, int bit_per_sample, int channel)
{
    AudioI2sCodec::Init(sample_rate, bit_per_sample, channel);

    i2s_data_bit_width_t bps = GetDataBitWidth(bit_per_sample);
    i2s_slot_mode_t ch = GetChannel(channel);

    if (duplex_driver_) 
    {
        bool ret = duplex_driver_->begin(I2S_MODE_STD, sample_rate, bps, ch);
        if (!ret) {
            Log::Error(TAG, "Failed to initialize I2S tx!");
            return false;
        }
    } 
    else 
    {
        if (tx_driver_) {
            bool ret = tx_driver_->begin(I2S_MODE_STD, sample_rate, bps, ch);
            if (!ret) {
                Log::Error(TAG, "Failed to initialize I2S tx!");
                return false;
            }
        }

        if (rx_driver_) {
            bool ret = rx_driver_->begin(I2S_MODE_STD, sample_rate, bps, ch);
            if (!ret) {
                Log::Error(TAG, "Failed to initialize I2S!");
                return false;
            }
        }
    }

    return true;
}

uint32_t AudioI2sSimple::Write(const int16_t* data, uint32_t samples) {
     
    I2sDriver *driver = (duplex_driver_) ? duplex_driver_ : tx_driver_;

    size_t bytes_write = driver->write((const uint8_t*)data, samples*2);
    return bytes_write;
}

uint32_t AudioI2sSimple::Read(int16_t* dest, uint32_t samples) {
    I2sDriver *driver = (duplex_driver_) ? duplex_driver_ : rx_driver_;

    size_t bytes_read = driver->readBytes((char *)dest, samples*2);
    return bytes_read;
}

AudioI2sSimple::~AudioI2sSimple() {
    if (duplex_driver_) 
    {
        duplex_driver_->end();
    } 
    else 
    {
        if (tx_driver_) {
            tx_driver_->end();
        }
        if (rx_driver_) {
            rx_driver_->end();
        }
    }
}

#endif //CONFIG_USE_AUDIO