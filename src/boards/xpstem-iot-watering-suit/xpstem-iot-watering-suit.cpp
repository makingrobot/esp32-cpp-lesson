#if BOARD_XPSTEM_IOT_WATERING_SUIT == 1

#include "xpstem-iot-watering-suit.h"

#include "src/sys/system_reset.h"
#include "src/boards/board.h"
#include "src/display/u8g2_display.h"
#include "src/boards/i2c_device.h"

#include "U8g2lib.h"

#include "board_config.h"

#define TAG "XPSTEM_IOT_WATERING_SUIT"

void* create_board() { 
    return new XPSTEM_IOT_WATERING_SUIT();
}

void XPSTEM_IOT_WATERING_SUIT::InitializeI2c() {
    ESP_LOGI( TAG, "Init I2C ......" );
    // Initialize I2C peripheral
    i2c_master_bus_config_t i2c_bus_cfg = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = 1,
        },
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &i2c_bus_));
}

void XPSTEM_IOT_WATERING_SUIT::InitializePowerSaveTimer() {
    ESP_LOGI( TAG, "Init power save timer ......" );
    power_save_timer_ = new PowerSaveTimer(-1, 180, 900);
    power_save_timer_->OnEnterSleepMode([this]() {
        //GetDisplay()->SetPowerSaveMode(true);
        GetBacklight()->SetBrightness(5);
        auto& app = Application::GetInstance();
        app.EnterSleepMode();
    });
    power_save_timer_->OnExitSleepMode([this]() {
        //GetDisplay()->SetPowerSaveMode(false);
        GetBacklight()->RestoreBrightness();
        auto& app = Application::GetInstance();
        app.ExitSleepMode();
    });
    power_save_timer_->OnShutdownRequest([this]() {
        //GetBacklight()->SetBrightness(0);
        auto& app = Application::GetInstance();
        app.Shutdown();
        
        GetLed()->TurnOff();
        esp_deep_sleep_start();
    });

    power_save_timer_->SetEnabled(true);
}

void XPSTEM_IOT_WATERING_SUIT::InitializeDisplay() {

    ESP_LOGI( TAG, "Create ssd1306 driver." );
    U8G2* u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, 
        /* reset=*/ U8X8_PIN_NONE, 
        /* clock=*/ I2C_SCL_PIN, 
        /* data=*/ I2C_SDA_PIN);  

    display_ = new U8g2Display(u8g2, 128, 64);
}

void XPSTEM_IOT_WATERING_SUIT::InitializeButtons() {
    ESP_LOGI( TAG, "Init button ......" );
//     //配置 GPIO
//     gpio_config_t io_conf = {
//         .pin_bit_mask = 1ULL << BUILTIN_LED_PIN,  // 设置需要配置的 GPIO 引脚
//         .mode = GPIO_MODE_OUTPUT,           // 设置为输出模式
//         .pull_up_en = GPIO_PULLUP_DISABLE,  // 禁用上拉
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,  // 禁用下拉
//         .intr_type = GPIO_INTR_DISABLE      // 禁用中断
//     };
//     gpio_config(&io_conf);  // 应用配置

//     boot_button_ = new Button(BOOT_BUTTON_PIN);
//     boot_button_->OnClick([this]() {
//         GetLed()->BlinkOnce();  // 闪烁1次
//         // do something.
//         auto& app = Application::GetInstance();
//         app.ToggleWorkState();
//     });

//     boot_button_->OnDoubleClick([this]() {
//         auto& app = Application::GetInstance();
//         app.Shutdown();

//         ESP_LOGI( TAG, "Entering deep sleep mode");
//         GetLed()->TurnOff();
//         esp_deep_sleep_start();
//     });
}

XPSTEM_IOT_WATERING_SUIT::XPSTEM_IOT_WATERING_SUIT() : WifiBoard() {

    ESP_LOGI(TAG, "===== Create Board ...... =====");

    InitializeI2c();

    InitializePowerSaveTimer();

    InitializeButtons();

    InitializeDisplay();

    ESP_LOGI( TAG, "===== Board config completed. =====");
}

XPSTEM_IOT_WATERING_SUIT::~XPSTEM_IOT_WATERING_SUIT() {
    
}

void XPSTEM_IOT_WATERING_SUIT::SetPowerSaveMode(bool enabled) {
    if (!enabled) {
        power_save_timer_->WakeUp();
    }
}

void XPSTEM_IOT_WATERING_SUIT::SetDisplay(Display* display) {
    display_ = reinterpret_cast<U8g2Display*>(display);
}

#endif //BOARD_XPSTEM_IOT_WATERING_SUIT