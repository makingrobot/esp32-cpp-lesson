/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_USE_LED_GPIO==1

#include "gpio_led.h"
#include "src/app/application.h"
#include <esp_log.h>
#include <Arduino.h>

#define TAG "GpioLed"

#define BLINK_INFINITE          -1

// GPIO_LED
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0

#define LEDC_FREQ               5000
#define LEDC_RESOLUTION         8
#define LEDC_DUTY               (8191)
#define LEDC_FADE_TIME          (1000)

// GPIO_LED
GpioLed::GpioLed(gpio_num_t gpio)
        : GpioLed(gpio, false) {
}

GpioLed::GpioLed(gpio_num_t gpio, int output_invert)
        : led_pin_(gpio), output_invert_(output_invert) {

    assert(gpio != GPIO_NUM_NC);

    pinMode(gpio, OUTPUT);

    blink_ticker_ = new Ticker();
}

GpioLed::~GpioLed() {
    if (blink_ticker_!=nullptr) {
        blink_ticker_->detach();
        blink_ticker_ = nullptr;
    }
}

void GpioLed::SetBrightness(uint8_t brightness) {
    brightness_ = brightness;
    analogWrite(led_pin_, brightness);
}

void GpioLed::TurnOn() {
    if (blink_ticker_->active()) {
        blink_ticker_->detach();
    }
    analogWrite(led_pin_, output_invert_ ? 0 : brightness_);
}

void GpioLed::TurnOff() {
    if (blink_ticker_->active()) {
        blink_ticker_->detach();
    }
    analogWrite(led_pin_, output_invert_ ? brightness_ : 0);
}

void GpioLed::BlinkOnce() {
    Blink(1, 100);
}

void GpioLed::Blink(int times, int interval_ms) {
    StartBlinkTask(times, interval_ms);
}

void GpioLed::StartContinuousBlink(int interval_ms) {
    StartBlinkTask(BLINK_INFINITE, interval_ms);
}

void TickerCallback(GpioLed *arg) {
    arg->OnBlinkTimer();
}

void GpioLed::StartBlinkTask(int times, int interval_ms) {
    if (blink_ticker_->active()) {
        blink_ticker_->detach();
    }
    blink_counter_ = times * 2;
    blink_interval_ms_ = interval_ms;
    blink_ticker_->attach_ms(interval_ms, TickerCallback, this);
}

void GpioLed::OnBlinkTimer() {
    std::lock_guard<std::mutex> lock(mutex_);
    blink_counter_--;
    if (blink_counter_ & 1) {
        TurnOn();
    } else {
        TurnOff();

        if (blink_counter_ == 0) {
            blink_ticker_->detach();
        }
    }
}

#endif //CONFIG_USE_LED_GPIO