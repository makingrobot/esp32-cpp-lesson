
#include "../audio_output.h"

/**
 * 缓存输出
 */
class AudioBufferOutput : public AudioOutput
{
public:
    AudioBufferOutput(AudioOutput *dest, int buf_size);
    virtual ~AudioBufferOutput() override;

    virtual uint32_t WriteSamples(const int16_t *data, uint32_t samples) override;
    virtual bool Stop() override;

    virtual bool SetRate(int hz) override;
    virtual bool SetBitsPerSample(int bits) override;
    virtual bool SetChannels(int channels) override;
    
protected:
    AudioOutput *output;
    int buffSize;
    int16_t *leftSample;
    int16_t *rightSample;
    int writePtr;
    int readPtr;
    bool filled;
};