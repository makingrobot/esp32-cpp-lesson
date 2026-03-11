/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_i2s_input.h"
#include "../../sys/log.h"

#define TAG "I2sInput"

bool AudioI2sInput::Init() {
    return false;
}

bool AudioI2sInput::Handle() {
    return false;
}

bool AudioI2sInput::Close() {
    return false;
}

int16_t* AudioI2sInput::GetSamples() {
    return 0;
}

#endif //CONFIG_USE_AUDIO