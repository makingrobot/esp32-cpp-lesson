/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _FILE_INPUT_H
#define _FILE_INPUT_H

#include <string>
#include <FS.h>
#include "../audio_input.h"

/**
 * 文件流输入
 */
class FileInput : public AudioInput {
public:
    FileInput(fs::File *audio_file) : audio_file_(audio_file) { }
    ~FileInput() { if (audio_file_) audio_file_->close(); }

    uint32_t Read(void *data, uint32_t len) override;
    bool Seek(int32_t pos, int dir) override;
    bool Close() override;

    size_t GetPosition() override { return (audio_file_) ? audio_file_->position() : -1; }
    size_t GetSize() override { return (audio_file_) ? audio_file_->size() : -1; }

private:
    fs::File *audio_file_;
    
};

#endif // _FILE_INPUT_H

#endif //CONFIG_USE_AUDIO