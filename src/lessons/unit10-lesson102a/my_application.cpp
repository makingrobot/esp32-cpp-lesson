/**
 * ESP32-Cpp-Lesson
 * ESP32 C++ 教程，基于ESP32-Arduino-Framework应用开发框架。
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
#include "src/framework/board/wifi_board.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/audio/input/audio_i2s_input.h"
#include "src/framework/audio/output/audio_file_output.h"
#include "src/framework/audio/output/audio_buffer_output.h"
#include "src/framework/audio/output/audio_encoder_output.h"
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
    // I2sInput（麦克风输入） -> Encoder（编码） -> Buffer（缓存写入） -> FileOutput（输出到文件）

    // I2S输入
    AudioCodec *audio_codec = Board::GetInstance().GetAudioCodec();
    AudioI2sInput *input = new AudioI2sInput(audio_codec);
    input->setSampleRate(44100);
    input->setBitPerSample(16);

    // 文件输出
    FS::File file;
    AudioFileOutput *file_output = new AudioFileOutput(file);
    AudioBufferOutput *buf_output = new AudioBufferOutput(file_output, 2048);
    // 编码输出
    AudioEncoderOutput *output = new AudioEncoderOutput(buf_output, "wav");

    // 音频管道
    AudioPipe *pipe = new AudioPipe();

    // 启动管道
    pipe->Start(input, output);
}

void MyApplication::OnLoop() {
    delay(1);
}

#endif 