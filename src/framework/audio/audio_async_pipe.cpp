/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 *
 */
#include "config.h"
#if CONFIG_USE_AUDIO == 1

#include "audio_async_pipe.h"
#include "../sys/log.h"
#include "../sys/mutex/frt_mutex.h"
#include "../sys/semaphore/frt_semaphore.h"

#define TAG "AudioAsyncPipe"

AudioAsyncPipe::AudioAsyncPipe() 
{
    audio_data_mutex_ = new FrtMutex();
    audio_data_semaphore_ = new FrtSemaphore();
}

void AudioAsyncPipe::Start(AudioInput *input, AudioOutput *output)
{
    input_ = input;
    output_ = output;

    // 启动输入任务
    xTaskCreate(
        [](void *parameter)
        {
            Log::Info(TAG, "AudioIn task running on core %d", xPortGetCoreID());

            AudioAsyncPipe *pipe = (AudioAsyncPipe *)parameter;
            pipe->InputTask();

            vTaskDelete(NULL);
        },                    /* 任务函数 TaskFunction_t */
        "AudioIn_Task",          /* 任务名称 const char* */
        8192,                 /* 堆栈字数 */
        this,                 /* 自定义参数指针 void* */
        tskIDLE_PRIORITY + 1, /* 任务优先级 UBaseType_t */
        &audio_in_handle_         /* 任务句柄指针 TaskHandle_t* */
    );
    
    // 启动输出任务
    xTaskCreate(
        [](void *parameter)
        {
            Log::Info(TAG, "AudioOut task running on core %d", xPortGetCoreID());

            AudioAsyncPipe *pipe = (AudioAsyncPipe *)parameter;
            pipe->OutputTask();

            vTaskDelete(NULL);
        },                    /* 任务函数 TaskFunction_t */
        "AudioOut_Task",          /* 任务名称 const char* */
        8192,                 /* 堆栈字数 */
        this,                 /* 自定义参数指针 void* */
        tskIDLE_PRIORITY + 1, /* 任务优先级 UBaseType_t */
        &audio_out_handle_         /* 任务句柄指针 TaskHandle_t* */
    );

    running_ = true;
}

void AudioAsyncPipe::InputTask()
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

    input_->SetAudioListener(audio_listener_);

    if (pipe_listener_) 
    {
        pipe_listener_(PipeAction::Begin);
    }

    // 处理数据
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

        MutexGuard lock_guard(audio_data_mutex_, -1);
        if (lock_guard.IsLocked()) {
            // 送入队列
            audio_data_queue_.push_back(input_data);
            audio_data_semaphore_->Notify(); //有数据了
        }
    }

    Log::Info(TAG, "audio input task end.");
    
}

void AudioAsyncPipe::OutputTask()
{
    // 初始化
    bool ret = output_->Init();
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

    output_->SetAudioListener(audio_listener_);

    while (running_)
    {
        if (audio_data_queue_.empty())
        { //队例无数据
            audio_data_semaphore_->Wait(1000); // 等待1s
            if (audio_data_queue_.empty()) 
            { //还是无数据
                continue;
            }
        }
        
        // 加锁后操作
        MutexGuard lock_guard(audio_data_mutex_, -1);
        if (!lock_guard.IsLocked()) 
        { //未拿到锁
            continue;
        }
        sample_data_t audio_data = std::move(audio_data_queue_.front());
        audio_data_queue_.pop_front();
        lock_guard.UnLock(); // 显式释放锁，默认为超出生命周期释放锁。

        // 数据过滤
        sample_data_t filter_data = {
            .samples = std::move(audio_data.samples),
            .length = audio_data.length
        };
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

    Log::Info(TAG, "audio output task end.");
}

void AudioAsyncPipe::Stop()
{
    running_ = false;
    delay(1000); // 等待1s

    output_->Close();
    input_->Close();
}

#endif