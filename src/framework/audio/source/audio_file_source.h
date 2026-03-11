/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_FILE_SOURCE_H
#define _AUDIO_FILE_SOURCE_H

#include <string>
#include <FS.h>
#include "../audio_source.h"

/**
 * 音频文件输入
 */
class AudioFileSource : public AudioSource {
public:
    AudioFileSource(fs::File &audio_file) : audio_file_(&audio_file) { }
    ~AudioFileSource() { if (audio_file_) audio_file_->close(); }

    uint32_t Read(void *data, uint32_t len) override;
    bool Seek(int32_t pos, int dir) override;
    bool Close() override;

    size_t GetPosition() override { return (audio_file_) ? audio_file_->position() : -1; }
    size_t GetSize() override { return (audio_file_) ? audio_file_->size() : -1; }

    const char* Tag() override { return "FileSource"; };

private:
    fs::File *audio_file_;
    
};

#endif // _AUDIO_FILE_SOURCE_H

#endif //CONFIG_USE_AUDIO