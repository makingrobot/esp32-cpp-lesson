/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_BUFFER_INPUT_H
#define _AUDIO_BUFFER_INPUT_H

#include <string>
#include "../audio_input.h"

/**
 * 音频缓存输入
 */
class AudioBufferInput : public AudioInput {
public:
    AudioBufferInput(AudioInput *source, uint32_t buf_size);
    AudioBufferInput(AudioInput *source, void *buffer, uint32_t buf_size);  //Pre-allocated buffer by app
    virtual ~AudioBufferInput();

    uint32_t Read(void *data, uint32_t len) override;
    bool Seek(int32_t pos, int dir) override;
    bool Close() override;

    size_t GetPosition() override { return (source_) ? source_->GetPosition() : -1; }
    size_t GetSize() override { return (source_) ? source_->GetSize() : -1; }

private:
    void Fill();

    AudioInput *source_;
    uint32_t buffSize;

    uint8_t *buffer;
    bool deallocateBuffer;
    uint32_t writePtr;
    uint32_t readPtr;
    uint32_t length;
    bool filled;

};

#endif // _AUDIO_BUFFER_INPUT_H

#endif //CONFIG_USE_AUDIO