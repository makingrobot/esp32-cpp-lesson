/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_no_codec.h"

#include <cmath>
#include <cstring>
#include <Arduino.h>
#include <driver/i2s.h>  //老版本esp32 i2s驱动

#include "../../sys/log.h"

#define TAG "AudioI2sNoCodec"

//-------- AudioI2sNoCodec Implements ---------------

void AudioI2sNoCodec::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample)
{
    AudioI2sCodec::Init(input_sample_rate, output_sample_rate, bit_per_sample);

    
}

uint32_t AudioI2sNoCodec::Write(const int16_t* data, uint32_t samples) {
    std::vector<int32_t> buffer(samples);

    for (int i = 0; i < samples; i++) {
        int16_t ms[2];
        ms[0] = data[i*2];
        ms[1] = data[i*2 + 1];
        MakeSampleStereo16( ms );

        if (mono_) {
            // Average the two samples and overwrite
            int32_t ttl = ms[0] + ms[1];
            ms[0] = ms[1] = (ttl>>1) & 0xffff;
        }
    
        buffer[i] = ((Amplify(ms[1])) << 16) | (Amplify(ms[0]) & 0xffff);
    }

    size_t bytes_write;
    i2s_write((i2s_port_t)1, (const char*)buffer.data(), sizeof(uint32_t), &bytes_write, 0);
    return bytes_write;

}

uint32_t AudioI2sNoCodec::Read(int16_t* dest, uint32_t samples) {
    size_t bytes_read;

    std::vector<int32_t> bit32_buffer(samples);
    // if (i2s_channel_read(rx_handle_, bit32_buffer.data(), samples * sizeof(int32_t), &bytes_read, portMAX_DELAY) != ESP_OK) {
    //     Log::Error(TAG, "Read Failed!");
    //     return 0;
    // }

    samples = bytes_read / sizeof(int32_t);
    for (int i = 0; i < samples; i++) {
        int32_t value = bit32_buffer[i] >> 12;
        dest[i] = (value > INT16_MAX) ? INT16_MAX : (value < -INT16_MAX) ? -INT16_MAX : (int16_t)value;
    }
    return samples;
}

AudioI2sNoCodec::~AudioI2sNoCodec() {
    
}

//------------------ AudioI2sNoCodecSimplex Implements -----------------

void AudioI2sNoCodecSimplex::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    if (use_apll_ == APLL_AUTO)
    {
        use_apll_ = APLL_ENABLE;
    }

    i2s_mode_t mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);

    i2s_comm_format_t comm_fmt;
    
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)
    comm_fmt = (i2s_comm_format_t) (I2S_COMM_FORMAT_STAND_I2S);
#else
    comm_fmt = (i2s_comm_format_t) (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
#endif
    
    i2s_bits_per_sample_t bps = I2S_BITS_PER_SAMPLE_16BIT;
    if (bit_per_sample == 24) bps = I2S_BITS_PER_SAMPLE_24BIT;
    else if (bit_per_sample == 32) bps = I2S_BITS_PER_SAMPLE_32BIT;

    i2s_config_t i2s_config_dac = {
          .mode = mode,
          .sample_rate = output_sample_rate,
          .bits_per_sample = bps,
          .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
          .communication_format = comm_fmt,
          .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // lowest interrupt priority
          .dma_buf_count = dma_buf_count_,
          .dma_buf_len = 128,
          .use_apll = use_apll_, // Use audio PLL
          .tx_desc_auto_clear = true, // Silence on underflow
          .fixed_mclk = false, //use_mclk, // Unused
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)
          .mclk_multiple = I2S_MCLK_MULTIPLE_256, // Unused
          .bits_per_chan = I2S_BITS_PER_CHAN_DEFAULT // Use bits per sample
#endif
    };
    Serial.printf("+%d %p\n", 1, &i2s_config_dac);
    if (i2s_driver_install((i2s_port_t)1, &i2s_config_dac, 0, NULL) != ESP_OK)
    {
        Serial.println("ERROR: Unable to install I2S drives\n");
    }
    
    i2s_pin_config_t pins = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = spk_bclk_,
        .ws_io_num = spk_ws_,
        .data_out_num = spk_dout_,
        .data_in_num = I2S_PIN_NO_CHANGE};

    i2s_set_pin((i2s_port_t)1, &pins);

    i2s_zero_dma_buffer((i2s_port_t)1);

    AudioI2sNoCodec::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

//------------------ AudioI2sNoCodecSimplexMic Implements -----------------

void AudioI2sNoCodecSimplexMic::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    // Create a new channel for speaker
    

    AudioI2sNoCodec::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

#endif //CONFIG_USE_AUDIO