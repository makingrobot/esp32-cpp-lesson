/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include <Arduino.h>
#include "audio_buffer_input.h"
#include "../../sys/log.h"

#define TAG "BufferInput"

AudioBufferInput::AudioBufferInput(AudioInput *source, uint32_t buff_size)
    : source_(source), buffSize(buff_size)
{
  buffer = (uint8_t*)malloc(sizeof(uint8_t) * buffSize);
  if (!buffer) Serial.printf_P(PSTR("Unable to allocate AudioBufferInput::buffer[]\n"));
  deallocateBuffer = true;
  writePtr = 0;
  readPtr = 0;
  length = 0;
  filled = false;
}

AudioBufferInput::AudioBufferInput(AudioInput *source, void *inBuff, uint32_t buff_size)
    : source_(source), buffSize(buff_size)
{
  buffer = (uint8_t*)inBuff;
  deallocateBuffer = false;
  writePtr = 0;
  readPtr = 0;
  length = 0;
  filled = false;
}

AudioBufferInput::~AudioBufferInput()
{
  if (deallocateBuffer) free(buffer);
  buffer = NULL;
}

uint32_t AudioBufferInput::Read(void *data, uint32_t len)
{
    if (!buffer) return source_->Read(data, len);

    uint32_t bytes = 0;
    if (!filled) {
        // Fill up completely before returning any data at all
        //cb.st(STATUS_FILLING, PSTR("Refilling buffer"));
        length = source_->Read(buffer, buffSize);
        writePtr = length % buffSize;
        filled = true;
    }

    // Pull from buffer until we've got none left or we've satisfied the request
    uint8_t *ptr = reinterpret_cast<uint8_t*>(data);
    uint32_t toReadFromBuffer = (len < length) ? len : length;
    if ( (toReadFromBuffer > 0) && (readPtr >= writePtr) ) {
        uint32_t toReadToEnd = (toReadFromBuffer < (uint32_t)(buffSize - readPtr)) ? toReadFromBuffer : (buffSize - readPtr);
        memcpy(ptr, &buffer[readPtr], toReadToEnd);
        readPtr = (readPtr + toReadToEnd) % buffSize;
        len -= toReadToEnd;
        length -= toReadToEnd;
        ptr += toReadToEnd;
        bytes += toReadToEnd;
        toReadFromBuffer -= toReadToEnd;
    }
    if (toReadFromBuffer > 0) { // We know RP < WP at this point
        memcpy(ptr, &buffer[readPtr], toReadFromBuffer);
        readPtr = (readPtr + toReadFromBuffer) % buffSize;
        len -= toReadFromBuffer;
        length -= toReadFromBuffer;
        ptr += toReadFromBuffer;
        bytes += toReadFromBuffer;
        toReadFromBuffer -= toReadFromBuffer;
    }

    if (len) {
        // Still need more, try direct read from src
        bytes += source_->Read(ptr, len);
        // We're out of buffered data, need to force a complete refill.  Thanks, @armSeb
        readPtr = 0;
        writePtr = 0;
        length = 0;
        filled = false;
        //cb.st(STATUS_UNDERFLOW, PSTR("Buffer underflow"));
    }

    Fill();

    return bytes;
}

bool AudioBufferInput::Seek(int32_t pos, int dir)
{
    if(dir == SEEK_CUR && (readPtr+pos) < length) {
        readPtr += pos;
        return true;
    } else {
        // Invalidate
        readPtr = 0;
        writePtr = 0;
        length = 0;
        return source_->Seek(pos, dir);
    }
}

bool AudioBufferInput::Close()
{
  if (deallocateBuffer) free(buffer);
  buffer = NULL;
  return source_->Close();
}

void AudioBufferInput::Fill()
{
    if (!buffer) return;

    if (length < buffSize) {
        // Now try and opportunistically fill the buffer
        if (readPtr > writePtr) {
        if (readPtr == writePtr+1) return;
        uint32_t bytesAvailMid = readPtr - writePtr - 1;
        int cnt = source_->Read(&buffer[writePtr], bytesAvailMid);
        length += cnt;
        writePtr = (writePtr + cnt) % buffSize;
        return;
        }

        if (buffSize > writePtr) {
        uint32_t bytesAvailEnd = buffSize - writePtr;
        int cnt = source_->Read(&buffer[writePtr], bytesAvailEnd);
        length += cnt;
        writePtr = (writePtr + cnt) % buffSize;
        if (cnt != (int)bytesAvailEnd) return;
        }

        if (readPtr > 1) {
        uint32_t bytesAvailStart = readPtr - 1;
        int cnt = source_->Read(&buffer[writePtr], bytesAvailStart);
        length += cnt;
        writePtr = (writePtr + cnt) % buffSize;
        }
    }
}

#endif