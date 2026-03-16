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
#if APP_LESSON101_A==1

#include <driver/i2s_std.h>
#include "my_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/audio/source/audio_file_source.h"
#include "src/framework/audio/source/audio_buffer_source.h"
#include "src/framework/audio/input/audio_decoder_input.h"
#include "src/framework/audio/output/audio_i2s_output.h"
#include "src/framework/audio/audio_codec.h"

#include "my_board.h"

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

    FileSystem *fs = Board::GetInstance().GetFileSystem();
    char *path = "/001.mp3";
    if (!fs->ExistsFile(path)) {
        Log::Warn(TAG, "file 001.mp3 not found.");
        return;
    }

    // 音频处理流
    // FileSource（文件源） -> Decoder（解码） -> I2sOutput（输出到喇叭）

    // 文件源
    AudioFileSource *file_source = new AudioFileSource(fs, std::string(path));

    // 解码输入
    AudioDecoderInput *input = new AudioDecoderInput(file_source, "mp3");

    // I2S输出
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();
    AudioI2sOutput *output = new AudioI2sOutput(audio_codec);

    // 音频管道
    AudioPipe *pipe = new AudioPipe();

    // 启动管道
    pipe->Start(input, output);
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 