/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_file_input.h"
#include "../../sys/log.h"

#define TAG "FileInput"

uint32_t AudioFileInput::Read(void *data, uint32_t len)
{
    return audio_file_->read(reinterpret_cast<uint8_t*>(data), len);
}

bool AudioFileInput::Seek(int32_t pos, int dir)
{
    if (!audio_file_) return false;
    if (dir==SEEK_SET) return audio_file_->seek(pos);
    else if (dir==SEEK_CUR) return audio_file_->seek(audio_file_->position() + pos);
    else if (dir==SEEK_END) return audio_file_->seek(audio_file_->size() + pos);
    return false;
}

bool AudioFileInput::Close()
{
    if (!audio_file_) {
        audio_file_->close();
        return true;
    }

    return false;
}

#endif