/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_AUDIO_CODER_WAV==1

#ifndef _WAV_DECODER_H
#define _WAV_DECODER_H

#include "../audio_encoder.h"
#include "../audio_source.h"
#include "../audio_status.h"

class WavEncoder : public AudioEncoder
{
public:
    WavEncoder();
    virtual ~WavEncoder();
    virtual bool Init() override;
    virtual sample_data_t Encode(const sample_data_t data) override;

private:
    
};

#endif //_WAV_ENCODER_H

#endif