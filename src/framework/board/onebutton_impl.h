#ifndef _ONEBUTTON_IMPL_H
#define _ONEBUTTON_IMPL_H

#include "button.h"

#include <Arduino.h>
#include <OneButton.h>

class OneButtonImpl : public Button {
public:
    OneButtonImpl(const int pin, const bool activeLow = true, const bool pullupActive = true) {
        button_ = new OneButton(pin, activeLow, pullupActive);
    }

    void BindAction(ButtonAction action) override { 

    }

    void OnClick(std::function<void()> click_func) override { 
        click_func_ = std::move(click_func);

        button_->attachClick([](void *param) {
            OneButtonImpl *_this = (OneButtonImpl*)param;
            _this->click_func_();
        }, this);
    }

    void OnClick(std::function<void(void*)> click_param_func, void *parameter) override  { 
        click_param_func_ = std::move(click_param_func);
        click_parameter_ = parameter;

        button_->attachClick([](void *param) {
            OneButtonImpl *_this = (OneButtonImpl*)param;
            _this->click_param_func_(_this->click_parameter_);
        }, this);
    }

    void OnDoubleClick(std::function<void()> doubleclick_func) override  { 
        doubleclick_func_ = std::move(doubleclick_func);

        button_->attachDoubleClick([](void *param) {
            OneButtonImpl *_this = (OneButtonImpl*)param;
            _this->doubleclick_func_();
        }, this);
    }

    void OnDoubleClick(std::function<void(void*)> doubleclick_param_func, void *parameter) override  { 
        doubleclick_param_func_ = std::move(doubleclick_param_func);
        doubleclick_parameter_ = parameter;

        button_->attachDoubleClick([](void *param) {
            OneButtonImpl *_this = (OneButtonImpl*)param;
            _this->doubleclick_param_func_(_this->doubleclick_parameter_);
        }, this);
    }

    bool IsPressed() override {
        return false;
    }

    void Tick() override {
        button_->tick();
    }

private:
    OneButton *button_;

    std::function<void()> click_func_;
    std::function<void(void*)> click_param_func_;
    void *click_parameter_;

    std::function<void()> doubleclick_func_;
    std::function<void(void*)> doubleclick_param_func_;
    void *doubleclick_parameter_;

    std::function<void()> longpress_func_;
    std::function<void(void*)> longpress_param_func_;
    void *longpress_parameter_;

};

#endif //_ONEBUTTON_IMPL_H