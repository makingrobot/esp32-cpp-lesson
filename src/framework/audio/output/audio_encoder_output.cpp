/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include <Arduino.h>
#include "audio_encoder_output.h"
#include "../encoder/wav_encoder.h"
#include "../../sys/log.h"

#define TAG "EncoderOutput"

AudioEncoderOutput::AudioEncoderOutput(FileSystem *fsys, const std::string &filename, const std::string& out_format) 
    : fsys_(fsys), filename_(filename), out_format_(out_format) {

}
    
AudioEncoderOutput::~AudioEncoderOutput() {
    Stop();
}

bool AudioEncoderOutput::Init() {
    Log::Info(TAG, "init...");
    if (fsys_->ExistsFile(filename_.c_str()))
    { // 存在就删除。
        fsys_->DeleteFile(filename_.c_str());
    }
    file_ = fsys_->OpenFile(filename_.c_str(), "w+");
    if (!file_)
    { // 以写入方式打开文件
        Log::Warn(TAG, "file %s open failed.", filename_);
        return false;
    }

    // 创建编码器
    if (out_format_ == "wav") {
#if CONFIG_AUDIO_CODER_WAV==1
        encoder_ = new WavEncoder();
#else
        #pragma message("Please set CONFIG_AUDIO_CODER_WAV=1 in config file when use WAV encode.")
#endif
    }
    
    if (!encoder_) {
        Log::Error(TAG, "encoder is null.");
        return false;
    }

    bool ret = encoder_->Init();
    if (!ret) {
        Log::Error(TAG, "encoder init fail.");
        return false;
    }

    uint8_t header[encoder_->GetHeaderSize()];
    memset(header, 0, sizeof(header));
    file_.write(header, sizeof(header));

    return true;
}

uint32_t AudioEncoderOutput::WriteSamples(const sample_data_t data) {

    // 数据预处理
    // TODO：是否要等待数据量足够后才能编码？

    // 编码处理
    sample_data_t enc_data = encoder_->Encode(data);

    // 写入文件
    size_t len = file_.write((uint8_t*)(enc_data.data), enc_data.length*2);
    // for (int i=0; i<(uint8_t)config_.channels; i++) {
    //     if ((uint8_t)config_.bits == 8) {
    //         uint8_t l = data.data[i] & 0xff;
    //         file_->write(&l, sizeof(l));
    //     } else {
    //         uint8_t l = data.data[i] & 0xff;
    //         uint8_t h = (data.data[i] >> 8) & 0xff;
    //         file_->write(&l, sizeof(l));
    //         file_->write(&h, sizeof(h));
    //     }
    // }

    return len;
}

bool AudioEncoderOutput::Stop()
{
    if (!file_)
        return false;

    uint8_t header[encoder_->GetHeaderSize()];
    encoder_->GetHeaderData(header, file_.size(), config_);

    // Write real header out
    file_.seek(0, SeekSet);
    file_.write(header, sizeof(header));

    file_.close();
    return true;
}

#endif