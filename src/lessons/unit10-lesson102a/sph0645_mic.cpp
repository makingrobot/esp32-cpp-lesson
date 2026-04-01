#include "config.h"
#if BOARD_LESSON102_A == 1

#include "sph0645_mic.h"
#include <driver/i2s.h>
#include <freertos/FreeRTOS.h>
#include <soc/i2s_reg.h>

#include "src/framework/sys/log.h"

#define TAG "Sph0645Mic"

bool Sph0645Mic::Init(const audio_config_t &config)
{
    AudioCodec::Init(config);
    
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 48000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S, //标准 I2S 格式 ，与 SPH0645 默认模式兼容
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 1024, //共 8KB 缓冲区，防止因 CPU 忙不过来导致录音断流；
        .use_apll = true  //启用音频专用锁相环（APLL），确保 48kHz 时钟精准，避免音调畸变；
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = bclk_pin_,
        .ws_io_num = ws_pin_,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = data_pin_
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);

    // Fixs for SPH0645
    REG_SET_BIT(I2S_TIMING_REG(I2S_NUM_0), BIT(9));
    REG_SET_BIT(I2S_CONF_REG(I2S_NUM_0), I2S_RX_MSB_SHIFT);

    i2s_set_pin(I2S_NUM_0, &pin_config);

    Log::Info(TAG, "i2s channel initialize success.");

    return true;
}

Sph0645Mic::~Sph0645Mic() 
{

}

uint32_t Sph0645Mic::Write(const int16_t* data, uint32_t samples) 
{    
    // dont use.
}

uint32_t Sph0645Mic::Read(int16_t* dest, uint32_t samples) 
{
    if (!input_enabled_) return 0;

    uint32_t raw_samples[samples];
    size_t bytes_read;

    i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * samples, &bytes_read, portMAX_DELAY);
    for (int i=0; i<samples; i++)
    {
        // 32bit -> 16bit
        int32_t temp = raw_samples[i] >> 11;
        dest[i] = (temp > INT16_MAX) ? INT16_MAX : (temp < -INT16_MAX) ? -INT16_MAX : (int16_t)temp;
    }
    return bytes_read;

}

#endif