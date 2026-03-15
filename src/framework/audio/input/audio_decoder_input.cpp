/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include <Arduino.h>
#include "audio_decoder_input.h"
#include "../decoder/helix_mp3_decoder.h"
#include "../decoder/wav_decoder.h"
#include "../../sys/log.h"

#define TAG "DecoderInput"

AudioDecoderInput::AudioDecoderInput(AudioSource *source, const std::string& in_format) 
    : source_(source), in_format_(in_format) {

}
    
AudioDecoderInput::~AudioDecoderInput() 
{
    decoder_ = nullptr;
}

bool AudioDecoderInput::Init() 
{
    Log::Info(TAG, "init...");
    bool ret = source_->Init();
    if (!ret) {
        Log::Error(TAG, "input source init fail.");
        return false;
    }

    // 创建解码器
    if (in_format_ == "mp3") {
        decoder_ = new HelixMP3Decoder(source_);
    } else if (in_format_ == "wav") {
        decoder_ = new WavDecoder(source_);
    }
    
    if (!decoder_) {
        Log::Error(TAG, "decoder is null.");
        return false;
    }

    ret = decoder_->Init();
    if (!ret) {
        Log::Error(TAG, "decoder init fail.");
        return false;
    }

    return true;
}

bool AudioDecoderInput::Handle() 
{
    return decoder_->Decode();
}

int16_t* AudioDecoderInput::GetSamples() 
{
    return decoder_->samples();
}

bool AudioDecoderInput::isEOF() 
{
    return decoder_->isEOF();
}

bool AudioDecoderInput::Close() 
{
    return source_->Close();
}

#endif