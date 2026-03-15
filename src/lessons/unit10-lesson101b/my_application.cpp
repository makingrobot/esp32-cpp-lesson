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

static const IPAddress ap_ip(192,168,5,1);
static const IPAddress ap_gateway(192,168,5,1);
static const IPAddress ap_subnet(255,255,255,0);

void* create_application() {
    return new MyApplication();
}

MyApplication::MyApplication() : Application() { 

}

void MyApplication::OnInit() {
    // 音频处理流
    // FileSource（文件源） -> Buffer（缓存读取） -> Decoder（解码） -> I2sOutput（输出到喇叭）

    // Http源
    FS::File file;
    AudioFileSource *file_source = new AudioFileSource(file);
    AudioBufferSource *buf_source = new AudioBufferSource(file_source, 2048);

    // 解码输入
    AudioDecoderInput *input = new AudioDecoderInput(buf_source, "mp3");

    // I2S输出
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();
    AudioI2sOutput *output = new AudioI2sOutput(audio_codec);
    output->setSampleRate(44100);
    output->setBitPerSample(16);

    // 音频管道
    AudioPipe *pipe = new AudioPipe();

    // 启动管道
    pipe->Start(input, output);
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 