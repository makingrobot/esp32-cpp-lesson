/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_PROGMEM_INPUT_H
#define _AUDIO_PROGMEM_INPUT_H

#include <string>
#include "../audio_input.h"

/**
 * 音频内存数据输入
 */
class AudioProgMemInput : public AudioInput {
public:
    AudioProgMemInput(const void *data, uint32_t len);
    ~AudioProgMemInput();

    uint32_t Read(void *data, uint32_t len) override;
    bool Seek(int32_t pos, int dir) override;
    bool Close() override;

    size_t GetPosition() override { return -1; }
    size_t GetSize() override { return progmemLen; }

private:
    const void *progmemData;
    uint32_t progmemLen;
    uint32_t memPointer;
    
};

#endif // _AUDIO_PROGMEM_INPUT_H

#endif //CONFIG_USE_AUDIO