/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_FILE_OUTPUT_H
#define _AUDIO_FILE_OUTPUT_H

#include "../audio_output.h"
#include "src/framework/file/file_system.h"

/**
 * 文件输出
 */
class AudioFileOutput : public AudioOutput {
public:
    AudioFileOutput(FileSystem *fsys, const std::string &filename) 
        : fsys_(fsys), filename_(filename) {  }
    virtual ~AudioFileOutput() { Stop(); }

    virtual bool Init() override;
    virtual uint32_t WriteSamples(const sample_data_t data) override;
    virtual bool Stop() override;
    virtual const char* Tag() override { return PSTR("FileOutput"); };

    void WriteHeader(const uint8_t data);

private:
    FileSystem *fsys_;
    const std::string filename_;
    fs::File file_;

};

#endif // _AUDIO_FILE_OUTPUT_H

#endif