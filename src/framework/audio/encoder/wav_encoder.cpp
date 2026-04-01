/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_AUDIO_CODER_WAV==1

#include <Arduino.h>
#include "wav_encoder.h"

// Hardcoded simple WAV header with 0xffffffff lengths all around
static const uint8_t HeaderTemplate[] PROGMEM = 
{ 
    0x52, 0x49, 0x46, 0x46, 0xff, 0xff, 0xff, 0xff, 
    0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20, 
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 
    0x22, 0x56, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00, 
    0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 
    0xff, 0xff, 0xff, 0xff 
};

WavEncoder::WavEncoder()
{

}

WavEncoder::~WavEncoder()
{

}

bool WavEncoder::Init()
{
    return true;
}

sample_data_t WavEncoder::Encode(const sample_data_t data)
{
    return data;
}

void WavEncoder::GetHeaderData(uint8_t *header, uint32_t file_len, audio_config_t config) const
{
    memcpy_P(header, HeaderTemplate, sizeof(HeaderTemplate));

    int chunksize = file_len - 8;
    header[4] = chunksize & 0xff;
    header[5] = (chunksize>>8)&0xff;
    header[6] = (chunksize>>16)&0xff;
    header[7] = (chunksize>>24)&0xff;

    header[22] = (uint8_t)config.channels & 0xff;
    header[23] = 0;

    header[24] = (uint32_t)config.rate & 0xff;
    header[25] = ((uint32_t)config.rate >> 8) & 0xff;
    header[26] = ((uint32_t)config.rate >> 16) & 0xff;
    header[27] = ((uint32_t)config.rate >> 24) & 0xff;
    int byteRate = (uint32_t)config.rate * (uint8_t)config.bits * (uint8_t)config.channels / 8;
    header[28] = byteRate & 0xff;
    header[29] = (byteRate >> 8) & 0xff;
    header[30] = (byteRate >> 16) & 0xff;
    header[31] = (byteRate >> 24) & 0xff;
    header[32] = (uint8_t)config.bits * (uint8_t)config.channels / 8;
    header[33] = 0;
    header[34] = (uint8_t)config.bits;
    header[35] = 0;

    int datasize = file_len - sizeof(header);
    header[40] = datasize & 0xff;
    header[41] = (datasize>>8)&0xff;
    header[42] = (datasize>>16)&0xff;
    header[43] = (datasize>>24)&0xff;
}

#endif