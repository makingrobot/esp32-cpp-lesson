/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson102：音频录制
 */
#include "config.h"
#if APP_LESSON102_A == 1

#ifndef _AUDIO_I2S_SPH0645_H
#define _AUDIO_I2S_SPH0645_H

#include <driver/gpio.h>
#include "src/framework/audio/codec/audio_i2s_simplex.h"

/**
 * SPH0645 I2S MEMS麦克风
 * 
 * SPH0645LM4H 工作在 Slave 模式
 * 典型的配置参数如下：
 * 采样率：16 kHz（覆盖人声主要频段）
 * 位深：24-bit（有效数据），传输用 32-bit 对齐
 * 声道：单声道（Mono）
 * 数据格式：左对齐 或 标准 I2S 
 */
class AudioI2sSph0645 : public AudioI2sSimplex {
public:
    AudioI2sSph0645(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, gpio_num_t mclk=GPIO_NUM_NC);

    virtual bool Init(const audio_config_t &config) override;
    virtual audio_config_t audio_config() override;
    virtual void EnableOutput(bool enable) override {  }

private:

};

#endif // _AUDIO_I2S_SPH0645_H

#endif