/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _STREAM_INPUT_H
#define _STREAM_INPUT_H

#include <string>
#include "../audio_input.h"


/**
 * 音频流输入基类
 */
class StreamInput : public AudioInput {
public:
    StreamInput() { }

private:

};

#endif // _STREAM_INPUT_H

#endif //CONFIG_USE_AUDIO