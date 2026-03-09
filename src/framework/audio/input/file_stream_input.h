/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _FILE_STREAM_INPUT_H
#define _FILE_STREAM_INPUT_H

#include <string>
#include <FS.h>
#include "stream_input.h"

/**
 * 文件流输入
 */
class FileStreamInput : public StreamInput {
public:
    FileStreamInput(const File &audio_file) : audio_file_(audio_file) { }

    int Read();

private:
    const File &audio_file_;

};

#endif // _FILE_STREAM_INPUT_H

#endif //CONFIG_USE_AUDIO