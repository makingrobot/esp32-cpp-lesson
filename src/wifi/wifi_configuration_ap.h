/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_WIFI_CONFIGURE_ENABLE==1

#ifndef _WIFI_CONFIGURATION_AP_H
#define _WIFI_CONFIGURATION_AP_H

#include <string>
#include <ESPAsyncWebServer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class WifiConfigurationAp {
public:
    static WifiConfigurationAp& GetInstance() {
        static WifiConfigurationAp instance;
        return instance;
    }

    WifiConfigurationAp() { }
    ~WifiConfigurationAp();

    void SetLanguage(const char* lang_code);
    void SetSsidPrefix(const char* ssid_prefix);
    void Start();

    std::string GetSsid();
    std::string GetWebServerUrl();

private:
    std::string GetAvailableAPList();
    std::string GetSavedAPList();
    bool ConnectToWifi(const std::string &ssid, const std::string &password);
    void LoadAdvancedConfig();

private:
    const char* lang_code_;
    const char* ssid_prefix_;

    // 高级配置项
    std::string ota_url_;
    int8_t max_tx_power_;
    bool remember_bssid_;

    AsyncWebServer* web_server_ = nullptr;
    //TaskHandle_t webrequest_handle_ = nullptr;
    char* request_data_ = nullptr;
    
};

#endif //_WIFI_CONFIGURATION_AP_H

#endif //CONFIG_WIFI_CONFIGURE_ENABLE