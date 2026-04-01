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
#if APP_LESSON102_A==1

#include <FS.h>
#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/display/display.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/audio/input/audio_i2s_input.h"
#include "src/framework/audio/output/audio_buffer_output.h"
#include "src/framework/audio/output/audio_encoder_output.h"
#include "src/framework/audio/audio_codec.h"
#include "my_board.h"

#define TAG "MyApplication"

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    Display *display = Board::GetInstance().GetDisplay();
    display->Rotate(1);

    FileSystem *fsys = Board::GetInstance().GetFileSystem();
    std::string filepath = "/1001.wav";

    display->GetWindow()->SetText(1, "Recording to file " + filepath);

    // 音频处理流
    // I2sInput（麦克风输入） -> Encoder（编码） -> Buffer（缓存写入） -> FileOutput（输出到文件）

    // I2S输入
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();
    AudioI2sInput *input = new AudioI2sInput(audio_codec);
    audio_config_t mic_config = {
        .rate = SAMPLE_RATE_48K,
        .bits = SAMPLE_BITS_16,
        .channels = CHANNELS_1
    };
    input->SetAudioConfig(mic_config);

    // 编码输出
    AudioEncoderOutput *output = new AudioEncoderOutput(fsys, filepath, "wav");
    output->SetAudioConfig(mic_config);

    // 音频管道
    pipe_ = new AudioPipe();

    // 事件监听
    pipe_->SetPipeListener([this](PipeAction action){
        AudioCodec *codec = Board::GetInstance().GetAudioCodec();
        if (action==PipeAction::Begin)
        {
            codec->EnableInput(true); // 使能输入
        }
        else if (action==PipeAction::Ended)
        {
            codec->EnableInput(false);
        }
        else if (action==PipeAction::Processing) 
        {
            info_count_++;
            if (info_count_ % 1000 == 0) 
            {  // 取整
                int n = (info_count_ / 1000) % 2;
                Display *display = Board::GetInstance().GetDisplay();
                display->GetWindow()->SetText(2, info_text_[n]);
            }
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
    MyBoard *board = (MyBoard*)(&Board::GetInstance());
    board->ButtonTick();
    delay(1);
}

bool MyApplication::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {
    if (button_name == kManualButton) {
        if (action == ButtonAction::DoubleClick) {
            pipe_->Stop();
            return true;
        }
    }

    return Application::OnPhysicalButtonEvent(button_name, action);
}

#endif 