#if BOARD_XPSTEM_IOT_WATERING_SUIT == 1

#ifndef _XPSTEM_IOT_WATERING_SUIT_H
#define _XPSTEM_IOT_WATERING_SUIT_H

#include <esp_log.h>
#include <esp_sleep.h>
#include <driver/i2c_master.h>
#include <driver/gpio.h>

#include "src/boards/button.h"
#include "src/app/application.h"
#include "src/boards/wifi_board.h"
#include "src/display/display.h"
#include "src/display/u8g2_display.h"
#include "src/power/power_save_timer.h"

class XPSTEM_IOT_WATERING_SUIT : public WifiBoard {
private:
    i2c_master_bus_handle_t i2c_bus_;
    Button* boot_button_ = nullptr;
    PowerSaveTimer* power_save_timer_ = nullptr;
    U8g2Display* display_ = nullptr;

    void InitializeI2c();
    void InitializePowerSaveTimer();
    void InitializeDisplay();
    void InitializeButtons();

public:
    XPSTEM_IOT_WATERING_SUIT();
    virtual ~XPSTEM_IOT_WATERING_SUIT();

    void SetPowerSaveMode(bool enabled) override;
    
    void SetDisplay(Display* display) override;
    Display* GetDisplay() override { return display_; }
    DispDriver* GetDispDriver() override { return nullptr; }
};

#endif //_XPSTEM_IOT_WATERING_SUIT_H

#endif //BOARD_XPSTEM_IOT_WATERING_SUIT