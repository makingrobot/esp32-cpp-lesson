/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_OUTPUT_H
#define _AUDIO_OUTPUT_H

#include <driver/gpio.h>

/**
 * 音频输出基类
 */
class AudioOutput {

};

#endif // _AUDIO_OUTPUT_H

#endif //CONFIG_USE_AUDIO