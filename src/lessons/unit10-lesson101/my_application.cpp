/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
 * 
 * 学习套件：https://www.xpstem.com/product/esp32-study-suit
 * Author: Billy Zhang（billy_zh@126.com）
 * 
 * Unit10-Lesson101：音频输出
 */
#include "config.h"
#if APP_LESSON101==1

#include <FS.h>
#include <driver/i2s_std.h>
#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "my_board.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/audio/input/audio_file_input.h"
#include "src/framework/audio/output/audio_i2s_output.h"
#include "src/framework/audio/audio_codec.h"

#define TAG "MyApplication"

static const IPAddress ap_ip(192,168,5,1);
static const IPAddress ap_gateway(192,168,5,1);
static const IPAddress ap_subnet(255,255,255,0);

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();

    fs::File f;
    AudioFileInput *input = new AudioFileInput(f);
    AudioI2sOutput *output = new AudioI2sOutput(audio_codec);
    output->setSampleRate(44000);
    output->setBitPerSample(16);

    // 建立一个音频管道
    AudioPipe *pipe = new AudioPipe(input, output);

    // 启动管道
    pipe->Start();
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 