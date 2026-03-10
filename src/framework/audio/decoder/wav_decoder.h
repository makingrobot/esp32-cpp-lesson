
#ifndef _WAV_DECODER_H
#define _WAV_DECODER_H

#include "../audio_decoder.h"
#include "../audio_input.h"

class WavDecoder : public AudioDecoder
{
public:
    WavDecoder(AudioInput &input);
    virtual ~WavDecoder();
    bool Init() override;
    bool Decode() override;
    void SetBufferSize(int sz) { buffSize = sz; }

private:
    bool ReadU32(uint32_t *dest) { return input_->Read(reinterpret_cast<uint8_t*>(dest), 4); }
    bool ReadU16(uint16_t *dest) { return input_->Read(reinterpret_cast<uint8_t*>(dest), 2); }
    bool ReadU8(uint8_t *dest) { return input_->Read(reinterpret_cast<uint8_t*>(dest), 1); }
    bool GetBufferedData(int bytes, void *dest);
    bool ReadWAVInfo();
    bool Stop();

    AudioInput *input_;

protected:
    // WAV info
    uint16_t channels;
    uint32_t sampleRate;
    uint16_t bitsPerSample;
    
    uint32_t availBytes;

    // We need to buffer some data in-RAM to avoid doing 1000s of small reads
    uint32_t buffSize;
    uint8_t *buff;
    uint16_t buffPtr;
    uint16_t buffLen;
};

#endif //_WAV_DECODER_H