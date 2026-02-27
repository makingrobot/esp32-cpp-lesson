#include "config.h"

#ifndef _MY_WINDOW_H
#define _MY_WINDOW_H

#include <TFT_eSPI.h>
#include <string>
#include "src/framework/display/tft_window.h"
#include "src/framework/sys/task.h"

class MyWindow : public TftWindow {
public:
    MyWindow();

    void Setup(TFT_eSPI* driver) override {
        driver_ = driver;
    }

    void SetStatus(const std::string& status) override { }
    void SetText(uint8_t line, const std::string& text) override { }
   
    void Start();
    
protected:
    void OnLoop();

private:

    TFT_eSPI* driver_ = nullptr;
    Task *task_ = nullptr;

};

#endif //_My_WINDOW_H
