/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_INPUT_H
#define _AUDIO_INPUT_H

#include <driver/gpio.h>

/**
 * 音频输入基类
 */
class AudioInput {

};

#endif // _AUDIO_INPUT_H

#endif //CONFIG_USE_AUDIO