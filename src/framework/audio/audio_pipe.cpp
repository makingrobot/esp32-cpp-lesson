/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 *
 */
#include "config.h"
#if CONFIG_USE_AUDIO == 1

#include "audio_pipe.h"
#include "../sys/log.h"

#define TAG "AudioPipe"

void AudioPipe::Start(AudioInput *input, AudioOutput *output)
{
    input_ = input;
    output_ = output;

    running_ = true;
    // 启动任务
    xTaskCreate(
        [](void *parameter)
        {
            Log::Info(TAG, "Pipe task running on core %d", xPortGetCoreID());

            AudioPipe *pipe = (AudioPipe *)parameter;
            pipe->Execute();

            vTaskDelete(NULL);
        },                    /* 任务函数 TaskFunction_t */
        "Pipe_Task",          /* 任务名称 const char* */
        8192,                 /* 堆栈字数 */
        this,                 /* 自定义参数指针 void* */
        tskIDLE_PRIORITY + 1, /* 任务优先级 UBaseType_t */
        &task_handle_         /* 任务句柄指针 TaskHandle_t* */
    );
}

void AudioPipe::Execute()
{
    // 初始化
    bool ret = input_->Init();
    if (!ret)
    {
        last_error_ = "audio input init fail.";
        Log::Error(TAG, last_error_.c_str());
        if (pipe_listener_) 
        {
            pipe_listener_(PipeAction::Error);
        }
        return;
    }

    ret = output_->Init();
    if (!ret)
    {
        last_error_ = "audio output init fail.";
        Log::Error(TAG, last_error_.c_str());
        if (pipe_listener_) 
        {
            pipe_listener_(PipeAction::Error);
        }
        return;
    }

    input_->SetAudioListener(audio_listener_);
    output_->SetAudioListener(audio_listener_);

    if (pipe_listener_) 
    {
        pipe_listener_(PipeAction::Begin);
    }

    // 处理数据
    // AudioInput使用Handle方法拉取数据；
    // AudioOutput使用WriteXxx方法推送数据；
    while (running_)
    {
        if (input_->isEOF()) break;

        if (pipe_listener_) 
        {
            pipe_listener_(PipeAction::Processing);
        }
    
        sample_data_t input_data;
        if (!input_->Handle(input_data)) 
        { // 无数据
            continue;
        }

        audio_listener_->OnDataInput(input_data);

        // move data
        sample_data_t filter_data = {
            .samples = std::move(input_data.samples),
            .length = input_data.length
        };
        // 数据过滤
        if (filter_list_.size() > 0)
        {
            bool success = true;
            for (AudioFilter *item : filter_list_)
            {
                sample_data_t out_data;
                if (!item->DoFilter(filter_data, out_data)) 
                {
                    success = false;
                    break;
                }
                // move data.
                filter_data = {
                    .samples = std::move(out_data.samples),
                    .length = out_data.length
                };
            }
            if (!success) 
            {
                continue;
            }
        }

        audio_listener_->OnDataOutput(filter_data);

        // 输出
        output_->WriteSamples(filter_data);
    }

    if (pipe_listener_) 
    {
        pipe_listener_(PipeAction::Ended);
    }

    Log::Info(TAG, "handle end.");
}

void AudioPipe::Stop()
{
    running_ = false;
    delay(1000); // 等待1s

    output_->Close();
    input_->Close();
}

#endif