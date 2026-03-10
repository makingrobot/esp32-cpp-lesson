
#include "audio_pipe.h"
#include "decoder/wav_decoder.h"
#include "../sys/log.h"

#define TAG "AudioPipe"

void AudioPipe::Start() {

    // 创建解码器
    decoder_ = new WavDecoder(*input_);

    // 创建编码器
    // encoder_;

    running_ = true;
    // 启动任务
    xTaskCreate(
        [](void *parameter) {
            Log::Info(TAG, "Pipe task running on core %d", xPortGetCoreID());
            
            AudioPipe* pipe = (AudioPipe *)parameter;
            pipe->Execute();

            vTaskDelete(NULL);
        },                      /* 任务函数 TaskFunction_t */
        "Pipe_Task",            /* 任务名称 const char* */
        8192,                   /* 堆栈字数 */
        this,                   /* 自定义参数指针 void* */
        tskIDLE_PRIORITY + 1,   /* 任务优先级 UBaseType_t */
        &task_handle_           /* 任务句柄指针 TaskHandle_t* */
    );
}

void AudioPipe::Execute() {

    // 初始化
    input_->Init();
    output_->Init();
    bool ret = decoder_->Init();
    if (!ret) {
        Log::Error(TAG, "Init fail.");
        return;
    }

    // 处理数据
    while (running_) {
        if (decoder_->Decode()) {
            int16_t* samples = decoder_->samples();

            
            // 中间处理


            // 输出
            output_->WriteSamples(samples, sizeof(samples) / sizeof(int16_t));
        }
    }
}

void AudioPipe::Stop() {
    running_ = false;
}