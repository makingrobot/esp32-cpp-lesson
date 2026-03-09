/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_DECODER_H
#define _AUDIO_DECODER_H

#include <driver/gpio.h>

/**
 * 音频解码器基类
 */
class AudioDecoder {

};

#endif // _AUDIO_DECODER_H

#endif //CONFIG_USE_AUDIO