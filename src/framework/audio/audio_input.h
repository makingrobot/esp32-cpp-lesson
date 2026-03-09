/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_INPUT_H
#define _AUDIO_INPUT_H

/**
 * 音频输入基类
 */
class AudioInput {
public:
    virtual uint32_t Read(void *data, uint32_t len) = 0;
    virtual bool Seek(int32_t pos, int dir) = 0;
    virtual bool Close() = 0;

    virtual size_t GetPosition() { return 0; }
    virtual size_t GetSize() { return 0; }
};

#endif // _AUDIO_INPUT_H

#endif //CONFIG_USE_AUDIO