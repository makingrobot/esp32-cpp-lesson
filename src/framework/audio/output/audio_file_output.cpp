/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include <vector>
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include "audio_file_output.h"
#include "../../sys/log.h"

#define TAG "AudioFileOutput"

bool AudioFileOutput::Init() 
{
    Log::Info(TAG, "init...");
    file_ = fsys_->OpenFile(filename_.c_str(), "w");
    if (!file_)
    {
        Log::Warn(TAG, "file %s open failed.", filename_);
        return false;
    }

    return true;
}

void AudioFileOutput::WriteHeader(const uint8_t data)
{
    //
}

uint32_t AudioFileOutput::WriteSamples(const sample_data_t data)
{
    return file_.write((uint8_t*)(data.data), data.length*2);
}

bool AudioFileOutput::Stop() 
{
    if (!file_)
        return false;

    file_.close();
    return true;
}

#endif //CONFIG_USE_AUDIO