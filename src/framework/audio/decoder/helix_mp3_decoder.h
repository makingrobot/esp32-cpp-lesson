
#ifndef _MP3_HELIX_DECODER_H
#define _MP3_HELIX_DECODER_H

#include "../audio_decoder.h"
#include "../audio_source.h"
#include "src/libs/helix-mp3/mp3dec.h"

class HelixMP3Decoder : public AudioDecoder
{
public:
    HelixMP3Decoder(AudioSource *source);
    virtual ~HelixMP3Decoder();
    bool Init() override;
    bool Decode() override;

private:
    bool FillBufferWithValidFrame(); // Read until we get a valid syncword and min(feof, 2048) butes in the buffer
    
    // Helix MP3 decoder
    HMP3Decoder hMP3Decoder;

    // Input buffering
    uint8_t buff[1600]; // File buffer required to store at least a whole compressed frame
    int16_t buffValid;
    int16_t lastFrameEnd;

    // Output buffering
    int16_t outSample[1152 * 2]; // Interleaved L/R
    int16_t validSamples;
    int16_t curSample;

    AudioSource *source_;
    
};

#endif //_MP3_HELIX_DECODER_H