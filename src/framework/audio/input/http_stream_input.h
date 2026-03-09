/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _HTTP_STREAM_INPUT_H
#define _HTTP_STREAM_INPUT_H

#include <string>
#include "stream_input.h"

/**
 * Http流式输入
 */
class HttpStreamInput : public StreamInput {
public:
    HttpStreamInput(const std::string &audio_url) : audio_url_(audio_url) { }

private:
    const std::string &audio_url_;

};

#endif // _HTTP_STREAM_INPUT_H

#endif //CONFIG_USE_AUDIO