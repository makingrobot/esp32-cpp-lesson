#include <Wire.h>

#include <functional>
#include <string>
#include <cstdint>
#include <queue>

/**
 * 与RP2040通信
 */
class RP2040Com {
public:
    RP2040Com(gpio_num_t clk_pin, gpio_num_t dat_pin, uint8_t address)
        clk_pin_(clk_pin), dat_pin_(dat_pin), address_(address_);
    
    void Start() {
        Wire.begin(address_, dat_pin_, clk_pin_, 100000);
        Wire.onRequest(OnRequestEvent);
        Wire.onReceive(OnReceiveEvent);
    }

    void Send(const char* data) {
        send_queue_.push(std::string(data));
    }

    void OnNewData(std::function<std::string)> on_newdata_handler) {
        on_newdata_handler_ = on_newdata_handler;
    }

private:
    gpio_num_t clk_pin_;
    gpio_num_t dat_pin_;
    uint8_t address_;
    bool waiting_for_data_ = false;
    uint8_t data_length_ = 0;
    std::function<void(std::string)> on_newdata_handler_;
    std::queue<std::string> send_queue_;

    // 发送数据
    void OnRequestEvent() {
        if (send_queue_.size() > 0) {
            std::string &dat = send_queue_.front();
            uint8_t len = (uint8_t)dat.length;
            Wire.write(len);  //发送数据长度
            Wire.write(dat.c_str(), len); //发送数据
        }
    }

    // 接收数据
    void OnReceiveEvent() {

        if (!waiting_for_data_ && Wire.available() > 1) {
            data_length_ = Wire.read();
            if (Wire.available() >= data_length_) {
                ReadData();
            } else {
                waiting_for_data_ = true;
            }
            return;
        }

        if (waiting_for_data_) {
            // 等到数据够了，读取
            if (Wire.available() >= data_length_) {
                ReadData();

            }
        }
    }

    void ReadData() {
        char dat[data_length_];
        for (int i=0; i<data_length_; i++) {
            dat[i] = Wire.read();
        }
        waiting_for_data_ = false;
        data_length_ = 0;

        if (on_newdata_handler_!=nullptr) {
            on_newdata_handler_(std::string(dat));
        }
    }

}