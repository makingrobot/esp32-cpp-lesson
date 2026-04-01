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
#if BOARD_LESSON102_A == 1

#ifndef _SPH0645_MIC_H
#define _SPH0645_MIC_H

#include <driver/gpio.h>
#include "src/framework/audio/audio_codec.h"

/**
 * SPH0645 MEMS麦克风
 * 
 * SPH0645LM4H 工作在 Slave 模式
 * 典型的配置参数如下：
 * 采样率：48 kHz（覆盖人声主要频段）
 * 位深：24-bit（有效数据），传输用 32-bit 对齐
 * 声道：单声道（Mono）
 * 数据格式：左对齐 或 标准 I2S 
 */
class Sph0645Mic : public AudioCodec {
public:
    Sph0645Mic(gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, gpio_num_t mclk=GPIO_NUM_NC) 
        :bclk_pin_(mic_sck), ws_pin_(mic_ws), data_pin_(mic_din), mclk_pin_(mclk)
    { 
    }
    virtual ~Sph0645Mic();

    virtual bool Init(const audio_config_t &config) override;
    virtual uint32_t Read(int16_t* dest, uint32_t samples) override;
    virtual uint32_t Write(const int16_t* data, uint32_t samples) override;
    
    virtual void EnableInput(bool enable) override { }

private:
    gpio_num_t bclk_pin_; 
    gpio_num_t ws_pin_; 
    gpio_num_t data_pin_; 
    gpio_num_t mclk_pin_;

};

#endif // _SPH0645_MIC_H

#endif