/*
*/

#include <Arduino.h>
#include "helix_mp3_decoder.h"

HelixMP3Decoder::HelixMP3Decoder(AudioInput &input) : input_(&input)
{
    hMP3Decoder = MP3InitDecoder();
    if (!hMP3Decoder) {
      Serial.printf_P(PSTR("Out of memory error! hMP3Decoder==NULL\n"));
      Serial.flush();
    }
    // For sanity's sake...
    memset(buff, 0, sizeof(buff));
    memset(outSample, 0, sizeof(outSample));
    buffValid = 0;
    lastFrameEnd = 0;
    validSamples = 0;
    curSample = 0;
    lastRate = 0;
    lastChannels = 0;
}

HelixMP3Decoder::~HelixMP3Decoder()
{
    MP3FreeDecoder(hMP3Decoder);
}

bool HelixMP3Decoder::Init()
{
    return true;
}

bool HelixMP3Decoder::Decode()
{
    // If we've got data, try and pump it out...
    if (validSamples) {
        samples_[0] = outSample[curSample*2];
        samples_[1] = outSample[curSample*2 + 1];
        validSamples--;
        curSample++;
        return true;
    }

    // No samples available, need to decode a new frame
    if (FillBufferWithValidFrame()) {
        // buff[0] start of frame, decode it...
        unsigned char *inBuff = reinterpret_cast<unsigned char *>(buff);
        int bytesLeft = buffValid;
        int ret = MP3Decode(hMP3Decoder, &inBuff, &bytesLeft, outSample, 0);
        if (ret) {
            // Error, skip the frame...
            // char buff[48];
            // sprintf(buff, "MP3 decode error %d", ret);
            // cb.st(ret, buff);
            return false;
        } 

        lastFrameEnd = buffValid - bytesLeft;
        MP3FrameInfo fi;
        MP3GetLastFrameInfo(hMP3Decoder, &fi);
        if ((int)fi.samprate!= (int)lastRate) {
          //output->SetRate(fi.samprate);
          lastRate = fi.samprate;
        }
        if (fi.nChans != lastChannels) {
          //output->SetChannels(fi.nChans);
          lastChannels = fi.nChans;
        }
        curSample = 0;
        validSamples = fi.outputSamps / lastChannels;

        return true;
    } 

    return false;
}

bool HelixMP3Decoder::FillBufferWithValidFrame()
{
    buff[0] = 0; // Destroy any existing sync word @ 0
    int nextSync;
    do {
        nextSync = MP3FindSyncWord(buff + lastFrameEnd, buffValid - lastFrameEnd);
        if (nextSync >= 0) nextSync += lastFrameEnd;
        lastFrameEnd = 0;
        if (nextSync == -1) {
            if (buff[buffValid-1]==0xff) { // Could be 1st half of syncword, preserve it...
                buff[0] = 0xff;
                buffValid = input_->Read(buff+1, sizeof(buff)-1);
                if (buffValid==0) return false; // No data available, EOF
            } else { // Try a whole new buffer
                buffValid = input_->Read(buff, sizeof(buff));
                if (buffValid==0) return false; // No data available, EOF
            }
        }
    } while (nextSync == -1);

    // Move the frame to start at offset 0 in the buffer
    buffValid -= nextSync; // Throw out prior to nextSync
    memmove(buff, buff+nextSync, buffValid);

    // We have a sync word at 0 now, try and fill remainder of buffer
    buffValid += input_->Read(buff + buffValid, sizeof(buff) - buffValid);

    return true;
}