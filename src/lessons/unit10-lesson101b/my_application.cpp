/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson101：音频输出
 */
#include "config.h"
#if APP_LESSON101_B==1

#include <driver/i2s_std.h>
#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/audio/source/audio_httpstream_source.h"
#include "src/framework/audio/source/audio_buffer_source.h"
#include "src/framework/audio/input/audio_decoder_input.h"
#include "src/framework/audio/output/audio_i2s_output.h"
#include "src/framework/audio/audio_codec.h"

#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    WifiBoard *board = (WifiBoard*)(&Board::GetInstance());    
    Display *display = board->GetDisplay();
    display->Rotate(1);
    
    //连接已有WiFi网络
    bool success = board->StartNetwork("qwer_1234", "billyhome", 10000);
    if (!success) {
        Log::Warn(TAG, "连接失败。");
        display->GetWindow()->SetText(1, "连接失败。");
        return;
    }

    std::string message = "IP:" + board->GetIpAddress();
    Log::Info(TAG, message.c_str());
    display->GetWindow()->SetText(1, message);
    
    std::string mp3_url = "http://www.xpstem.com/demo/test.mp3";
    display->GetWindow()->SetText(1, "Play url " + mp3_url);
    
    // 音频处理流
    // Http源 -> Buffer（缓存读取） -> Decoder（解码） -> I2sOutput（输出到喇叭）

    // Http源
    AudioHttpStreamSource *http_source = new AudioHttpStreamSource(mp3_url);
    //AudioBufferSource *buf_source = new AudioBufferSource(http_source, 2048);

    // 解码输入
    AudioDecoderInput *input = new AudioDecoderInput(http_source, "mp3");

    // I2S输出
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();
    AudioI2sOutput *output = new AudioI2sOutput(audio_codec);

    // 音频管道
    pipe_ = new AudioPipe();

    // 事件监听
    pipe_->SetPipeListener([this](PipeAction action){
        AudioCodec *codec = Board::GetInstance().GetAudioCodec();
        if (action==PipeAction::Begin)
        {
            codec->EnableOutput(true); // 使能输出
        }
        else if (action==PipeAction::Ended)
        {
            codec->EnableOutput(false);
        }
        else if (action==PipeAction::Error)
        {
            Display *display = Board::GetInstance().GetDisplay();
            display->GetWindow()->SetText(3, pipe_->last_error());
        }
    });

    // 启动管道
    pipe_->Start(input, output);
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 