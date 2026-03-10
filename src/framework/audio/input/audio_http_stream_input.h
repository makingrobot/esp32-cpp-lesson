/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_HTTP_STREAM_INPUT_H
#define _AUDIO_HTTP_STREAM_INPUT_H

#include <string>
#include "audio_input.h"

/**
 * 音频Http流式输入
 */
class AudioHttpStreamInput : public AudioInput {
public:
    AudioHttpStreamInput(const std::string &audio_url) : audio_url_(audio_url) { }

    uint32_t Read(void *data, uint32_t len) override;
    bool Seek(int32_t pos, int dir) override;
    bool Close() override;

    size_t GetPosition() override;
    size_t GetSize() override;

private:
    const std::string audio_url_;

};

#endif // _AUDIO_HTTP_STREAM_INPUT_H

#endif //CONFIG_USE_AUDIO