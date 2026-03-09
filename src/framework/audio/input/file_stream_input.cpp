/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "file_stream_input.h"
#include "../../sys/log.h"

#define TAG "FileStreamInput"

int FileStreamInput::Read() 
{
    return 0;
}

#endif