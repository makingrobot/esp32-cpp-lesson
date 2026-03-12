/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_no_codec3.h"

#include <cmath>
#include <cstring>
#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#include "../../sys/log.h"

#define TAG "AudioI2sNoCodec3"

//-------- AudioI2sNoCodec3 Implements ---------------

void AudioI2sNoCodec3::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample)
{
    AudioI2sCodec::Init(input_sample_rate, output_sample_rate, bit_per_sample);

    if (tx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_enable(tx_handle_));
    }

    if (rx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_enable(rx_handle_));
    }
}

uint32_t AudioI2sNoCodec3::Write(const int16_t* data, uint32_t samples) {
    std::vector<int32_t> buffer(samples);

    // output_volume_: 0-100
    // volume_factor_: 0-65536
    int32_t volume_factor = pow(double(output_volume_) / 100.0, 2) * 65536;
    for (int i = 0; i < samples; i++) {
        int64_t temp = int64_t(data[i]) * volume_factor; // 使用 int64_t 进行乘法运算
        if (temp > INT32_MAX) {
            buffer[i] = INT32_MAX;
        } else if (temp < INT32_MIN) {
            buffer[i] = INT32_MIN;
        } else {
            buffer[i] = static_cast<int32_t>(temp);
        }
    }

    size_t bytes_written;
    ESP_ERROR_CHECK(i2s_channel_write(tx_handle_, buffer.data(), samples * sizeof(int32_t), &bytes_written, portMAX_DELAY));
    return bytes_written / sizeof(int32_t);
}

uint32_t AudioI2sNoCodec3::Read(int16_t* dest, uint32_t samples) {
    size_t bytes_read;

    std::vector<int32_t> bit32_buffer(samples);
    if (i2s_channel_read(rx_handle_, bit32_buffer.data(), samples * sizeof(int32_t), &bytes_read, portMAX_DELAY) != ESP_OK) {
        Log::Error(TAG, "Read Failed!");
        return 0;
    }

    samples = bytes_read / sizeof(int32_t);
    for (int i = 0; i < samples; i++) {
        int32_t value = bit32_buffer[i] >> 12;
        dest[i] = (value > INT16_MAX) ? INT16_MAX : (value < -INT16_MAX) ? -INT16_MAX : (int16_t)value;
    }
    return samples;
}

AudioI2sNoCodec3::~AudioI2sNoCodec3() {
    if (rx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_disable(rx_handle_));
    }
    if (tx_handle_ != nullptr) {
        ESP_ERROR_CHECK(i2s_channel_disable(tx_handle_));
    }
}

//------------------ AudioI2sNoCodec3Duplex Implements -----------------

void AudioI2sNoCodec3Duplex::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    i2s_chan_config_t chan_cfg = {
        .id = I2S_NUM_0,
        .role = I2S_ROLE_MASTER,
        .dma_desc_num = AUDIO_CODEC_DMA_DESC_NUM,
        .dma_frame_num = AUDIO_CODEC_DMA_FRAME_NUM,
        .auto_clear_after_cb = true,
        .auto_clear_before_cb = false,
        .intr_priority = 0,
    };
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle_, &rx_handle_));

    i2s_data_bit_width_t bit_width = GetDataBitWidth(bit_per_sample);

    i2s_std_config_t std_cfg = {
        .clk_cfg = {
            .sample_rate_hz = (uint32_t)output_sample_rate_,
            .clk_src = I2S_CLK_SRC_DEFAULT,
            .mclk_multiple = I2S_MCLK_MULTIPLE_256,
			#ifdef   I2S_HW_VERSION_2
				.ext_clk_freq_hz = 0,
			#endif

        },
        .slot_cfg = {
            .data_bit_width = bit_width,
            .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
            .slot_mode = I2S_SLOT_MODE_MONO,
            .slot_mask = I2S_STD_SLOT_LEFT,
            .ws_width = bit_width,
            .ws_pol = false,
            .bit_shift = true,
            #ifdef   I2S_HW_VERSION_2
                .left_align = true,
                .big_endian = false,
                .bit_order_lsb = false
            #endif

        },
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = bclk_,
            .ws = ws_,
            .dout = dout_,
            .din = din_,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false
            }
        }
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle_, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle_, &std_cfg));
    Log::Info(TAG, "Duplex channels created");

    AudioI2sNoCodec3::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

//------------------ AudioI2sNoCodec3Simplex Implements -----------------

void AudioI2sNoCodec3Simplex::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    // Create a new channel for speaker
    i2s_chan_config_t chan_cfg = {
        .id = I2S_NUM_0,
        .role = I2S_ROLE_MASTER,
        .dma_desc_num = AUDIO_CODEC_DMA_DESC_NUM,
        .dma_frame_num = AUDIO_CODEC_DMA_FRAME_NUM,
        .auto_clear_after_cb = true,
        .auto_clear_before_cb = false,
        .intr_priority = 0,
    };
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle_, nullptr));

    i2s_data_bit_width_t bit_width = GetDataBitWidth(bit_per_sample);
    
    i2s_std_config_t std_cfg = {
        .clk_cfg = {
            .sample_rate_hz = (uint32_t)output_sample_rate,
            .clk_src = I2S_CLK_SRC_DEFAULT,
            .mclk_multiple = I2S_MCLK_MULTIPLE_256,
			#ifdef   I2S_HW_VERSION_2
				.ext_clk_freq_hz = 0,
			#endif

        },
        .slot_cfg = {
            .data_bit_width = bit_width,
            .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
            .slot_mode = I2S_SLOT_MODE_MONO,
            .slot_mask = I2S_STD_SLOT_LEFT,
            .ws_width = bit_width,
            .ws_pol = false,
            .bit_shift = true,
            #ifdef   I2S_HW_VERSION_2
                .left_align = true,
                .big_endian = false,
                .bit_order_lsb = false
            #endif

        },
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = spk_bclk_,
            .ws = spk_ws_,
            .dout = spk_dout_,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false
            }
        }
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle_, &std_cfg));

    Log::Info(TAG, "tx channels created");

    if (duplex_) 
    {
        // Create a new channel for MIC
        chan_cfg.id = I2S_NUM_1;
        ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, nullptr, &rx_handle_));

        std_cfg.clk_cfg.sample_rate_hz = (uint32_t)input_sample_rate;
        std_cfg.gpio_cfg.bclk = mic_sck_;
        std_cfg.gpio_cfg.ws = mic_ws_;
        std_cfg.gpio_cfg.dout = I2S_GPIO_UNUSED;
        std_cfg.gpio_cfg.din = mic_din_;

        ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle_, &std_cfg));
        Log::Info(TAG, "rx channels created");
    }

    AudioI2sNoCodec3::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

//------------------ AudioI2sNoCodec3SimplexMic Implements -----------------

void AudioI2sNoCodec3SimplexMic::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    // Create a new channel for speaker
    i2s_chan_config_t chan_cfg = {
        .id = I2S_NUM_1,
        .role = I2S_ROLE_MASTER,
        .dma_desc_num = AUDIO_CODEC_DMA_DESC_NUM,
        .dma_frame_num = AUDIO_CODEC_DMA_FRAME_NUM,
        .auto_clear_after_cb = true,
        .auto_clear_before_cb = false,
        .intr_priority = 0,
    };
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, nullptr, &rx_handle_));

    i2s_data_bit_width_t bit_width = GetDataBitWidth(bit_per_sample);
    
    i2s_std_config_t std_cfg = {
        .clk_cfg = {
            .sample_rate_hz = (uint32_t)input_sample_rate,
            .clk_src = I2S_CLK_SRC_DEFAULT,
            .mclk_multiple = I2S_MCLK_MULTIPLE_256,
			#ifdef   I2S_HW_VERSION_2
				.ext_clk_freq_hz = 0,
			#endif

        },
        .slot_cfg = {
            .data_bit_width = bit_width,
            .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
            .slot_mode = I2S_SLOT_MODE_MONO,
            .slot_mask = I2S_STD_SLOT_LEFT,
            .ws_width = bit_width,
            .ws_pol = false,
            .bit_shift = true,
            #ifdef   I2S_HW_VERSION_2
                .left_align = true,
                .big_endian = false,
                .bit_order_lsb = false
            #endif

        },
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = mic_sck_,
            .ws = mic_ws_,
            .dout = I2S_GPIO_UNUSED,
            .din = mic_din_,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false
            }
        }
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle_, &std_cfg));

    Log::Info(TAG, "rx channels created");

    AudioI2sNoCodec3::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

//---------------------- AudioI2sNoCodec3SimplexPdm --------------------------------

void AudioI2sNoCodec3SimplexPdm::Init(int input_sample_rate, int output_sample_rate, int bit_per_sample) {
    
    // Create a new channel for speaker
    i2s_chan_config_t tx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    tx_chan_cfg.dma_desc_num = AUDIO_CODEC_DMA_DESC_NUM;
    tx_chan_cfg.dma_frame_num = AUDIO_CODEC_DMA_FRAME_NUM;
    tx_chan_cfg.auto_clear_after_cb = true;
    tx_chan_cfg.auto_clear_before_cb = false;
    tx_chan_cfg.intr_priority = 0;
    ESP_ERROR_CHECK(i2s_new_channel(&tx_chan_cfg, &tx_handle_, NULL));

    i2s_data_bit_width_t bit_width = GetDataBitWidth(bit_per_sample);

    i2s_std_config_t tx_std_cfg = {
        .clk_cfg = {
            .sample_rate_hz = (uint32_t)output_sample_rate,
            .clk_src = I2S_CLK_SRC_DEFAULT,
            .mclk_multiple = I2S_MCLK_MULTIPLE_256,
			#ifdef   I2S_HW_VERSION_2
				.ext_clk_freq_hz = 0,
			#endif

        },
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(bit_width, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = spk_bclk_,
            .ws = spk_ws_,
            .dout = spk_dout_,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv   = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle_, &tx_std_cfg));

#if SOC_I2S_SUPPORTS_PDM_RX
    // Create a new channel for MIC in PDM mode
    i2s_chan_config_t rx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_1, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&rx_chan_cfg, NULL, &rx_handle_));

    i2s_pdm_rx_config_t pdm_rx_cfg = {
        .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG((uint32_t)input_sample_rate),
        /* The data bit-width of PDM mode is fixed to 16 */
        .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .clk = mic_sck_,
            .din = mic_din_,

            .invert_flags = {
                .clk_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_pdm_rx_mode(rx_handle_, &pdm_rx_cfg));
#else
    Log::Error(TAG, "PDM is not supported");
#endif
    Log::Info(TAG, "Simplex channels created");

    AudioI2sNoCodec3::Init(input_sample_rate, output_sample_rate, bit_per_sample);
}

uint32_t AudioI2sNoCodec3SimplexPdm::Read(int16_t* dest, uint32_t samples) {
    size_t bytes_read;

    // PDM 解调后的数据位宽为 16 位，直接读取到目标缓冲区
    if (i2s_channel_read(rx_handle_, dest, samples * sizeof(int16_t), &bytes_read, portMAX_DELAY) != ESP_OK) {
        Log::Error(TAG, "Read Failed!");
        return 0;
    }

    // 计算实际读取的样本数
    return bytes_read / sizeof(int16_t);
}

#endif //CONFIG_USE_AUDIO