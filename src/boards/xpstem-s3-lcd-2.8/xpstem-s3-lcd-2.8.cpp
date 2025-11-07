#include "config.h"
#if BOARD_XPSTEM_S3_LCD_2_80 == 1

#include "xpstem-s3-lcd-2.8.h"

#include "src/sys/system_reset.h"
#include "src/boards/board.h"
#include "src/boards/i2c_device.h"
#include "src/led/ws2812_led.h"
#include "src/display/drivers/ili9341/ili9341_driver.h"
#include "src/audio/codecs/es8311/es8311_audio_codec.h"
#include "src/sys/time/ntp_time.h"
#include <SD_MMC.h>

#define TAG "XPSTEM_S3_LCD_2_80"

void* create_board() { 
    return new XPSTEM_S3_LCD_2_80();
}

void XPSTEM_S3_LCD_2_80::InitializeI2c() {
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

void XPSTEM_S3_LCD_2_80::InitializeSPI() {
    
    ESP_LOGI( TAG, "Init SPI for lcd driver ......" );
    spi_bus_config_t buscfg = {};
    buscfg.mosi_io_num = DISPLAY_MOSI_PIN;
    buscfg.miso_io_num = DISPLAY_MISO_PIN;
    buscfg.sclk_io_num = DISPLAY_SCK_PIN;
    buscfg.quadwp_io_num = GPIO_NUM_NC;
    buscfg.quadhd_io_num = GPIO_NUM_NC;
    buscfg.max_transfer_sz = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t); // for lcd.
    ESP_ERROR_CHECK(spi_bus_initialize(spi_host, &buscfg, SPI_DMA_CH_AUTO));

}

void XPSTEM_S3_LCD_2_80::InitializePowerSaveTimer() {
    ESP_LOGI( TAG, "Init power save timer ......" );
    power_save_timer_ = new PowerSaveTimer(-1, 180, 900);
    power_save_timer_->OnEnterSleepMode([this]() {
        EnterSleepMode();
    });
    power_save_timer_->OnExitSleepMode([this]() {
        ExitSleepMode();
    });
    power_save_timer_->OnShutdownRequest([this]() {
        Shutdown();
    });

    power_save_timer_->SetEnabled(true);
}

void XPSTEM_S3_LCD_2_80::InitializeDisplay() {
    ESP_LOGI( TAG, "Init lcd display ......" );

    ESP_LOGI( TAG, "Create ili9341 driver." );
    lcd_driver_ = new ILI9341Driver(DISPLAY_WIDTH, DISPLAY_HEIGHT,
                                    DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y, DISPLAY_SWAP_XY, 
                                    DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y);

                                    
    ESP_LOGI( TAG, "Init ili9341 on spi mode." );
    lcd_driver_->InitSpi(SPI3_HOST, DISPLAY_SPI_MODE, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 
        DISPLAY_MOSI_PIN, GPIO_NUM_NC, DISPLAY_CLK_PIN, DISPLAY_RGB_ORDER, DISPLAY_INVERT_COLOR);

}

void XPSTEM_S3_LCD_2_80::I2cDetect() {
    uint8_t address;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            address = i + j;
            esp_err_t ret = i2c_master_probe(i2c_bus_, address, pdMS_TO_TICKS(200));
            if (ret == ESP_OK) {
                printf("%02x ", address);
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf("UU ");
            } else {
                printf("-- ");
            }
        }
        printf("\r\n");
    }
}

void XPSTEM_S3_LCD_2_80::InitializeButtons() {
    ESP_LOGI( TAG, "Init button ......" );
    //配置 GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << BUILTIN_LED_PIN,  // 设置需要配置的 GPIO 引脚
        .mode = GPIO_MODE_OUTPUT,           // 设置为输出模式
        .pull_up_en = GPIO_PULLUP_DISABLE,  // 禁用上拉
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  // 禁用下拉
        .intr_type = GPIO_INTR_DISABLE      // 禁用中断
    };
    gpio_config(&io_conf);  // 应用配置

    boot_button_ = new Button(BOOT_BUTTON_PIN);
    boot_button_->OnClick([this]() {
        OnPhysicalButtonEvent("boot", "click");
    });

    boot_button_->OnDoubleClick([this]() {
        OnPhysicalButtonEvent("boot", "double_click");
    });
}

void XPSTEM_S3_LCD_2_80::InitializeFt6336TouchPad() {
    ESP_LOGI( TAG, "Init FT6336 touch ......" );
    ft6336_ = new Ft6336(i2c_bus_, TOUCH_FT6336_ADDR);
    ft6336_->OnTouched([this](const TouchPoint_t& tp) {
        OnDisplayTouchEvent(tp);
    });
    ft6336_->Start();
}

void XPSTEM_S3_LCD_2_80::InitializeFileSystem() {
    ESP_LOGI( TAG, "Init SD MMC ......" );
    if (!SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D1, SD_MMC_D2, SD_MMC_D3, SD_MMC_D4)) {
        ESP_LOGW(TAG, "Set SD MMC pin change failed!");
        return;
    }

    if (!SD_MMC.begin()) {
        ESP_LOGW(TAG, "SD Card mount failed!");
        return;
    }

    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
        ESP_LOGW(TAG, "No SD_MMC card attached");
        return;
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    ESP_LOGI(TAG, "SD_MMC Card Size: %lluMB\n", cardSize);

    file_system_ = new FileSystem(SD_MMC);
}

XPSTEM_S3_LCD_2_80::XPSTEM_S3_LCD_2_80() : WifiBoard() {

    ESP_LOGI(TAG, "===== Create Board ...... =====");

    ESP_LOGI( TAG, "Init led ......" );
    led_ = new Ws2812Led(BUILTIN_LED_PIN);

    InitializeI2c();
    //I2cDetect();

    InitializeSPI();

    InitializeButtons();

    InitializeDisplay();

    ESP_LOGI( TAG, "Init backlight ......" );
    backlight_ = new PwmBacklight(DISPLAY_BACKLIGHT_PIN, DISPLAY_BACKLIGHT_OUTPUT_INVERT);
    backlight_->RestoreBrightness();

    InitializeFt6336TouchPad();

    ESP_LOGI( TAG, "Init audio codec ......" );
    /* 使用ES8311 驱动 */
    audio_codec_ = new Es8311AudioCodec(
        i2c_bus_, 
        I2C_NUM_0, 
        AUDIO_INPUT_SAMPLE_RATE, 
        AUDIO_OUTPUT_SAMPLE_RATE,
        AUDIO_I2S_MCLK_PIN, 
        AUDIO_I2S_BCLK_PIN, 
        AUDIO_I2S_WS_PIN, 
        AUDIO_I2S_DOUT_PIN, 
        AUDIO_I2S_DIN_PIN,
        AUDIO_CODEC_PA_PIN, 
        AUDIO_CODEC_ES8311_ADDR,
        true,
        true);

    //InitializeFileSystem();

    //time_ = new NTPTime();

    ESP_LOGI( TAG, "Init battery monitor ......" );
    battery_monitor_ = new AdcBatteryMonitor(BATTERY_ADC_PIN, BATTERY_ADC_UNIT, BATTERY_ADC_CHANNEL, 200000, 200000);

    InitializePowerSaveTimer();

    ESP_LOGI( TAG, "===== Board config completed. =====");
}

XPSTEM_S3_LCD_2_80::~XPSTEM_S3_LCD_2_80() {
    
}

bool XPSTEM_S3_LCD_2_80::GetBatteryLevel(int &level, bool &charging, bool &discharging) {
    charging = battery_monitor_->IsCharging();
    discharging = !charging;
    level = battery_monitor_->GetBatteryLevel();
    return true;
}

void XPSTEM_S3_LCD_2_80::SetPowerSaveMode(bool enabled) {
    if (!enabled) {
        power_save_timer_->WakeUp();
    }
}

void XPSTEM_S3_LCD_2_80::SetDisplay(Display* display) {
    display_ = reinterpret_cast<LvglDisplay*>(display);
    display_->SetupUI();
}

#endif //BOARD_XPSTEM_S3_LCD_2_80