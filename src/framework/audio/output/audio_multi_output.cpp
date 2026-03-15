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
#include "audio_multi_output.h"
#include "../../sys/log.h"

#define TAG "AudioMultiOutput"

bool AudioMultiOutput::Init() 
{
    for (auto& item : output_list_) {
        item->Init();
    }
}

uint32_t AudioMultiOutput::WriteSamples(const int16_t *data, uint32_t samples)
{
    for (auto& item : output_list_) {
        item->WriteSamples(data, samples);
    }
}

bool AudioMultiOutput::Stop() 
{
    for (auto& item : output_list_) {
        item->Stop();
    }
}

#endif //CONFIG_USE_AUDIO