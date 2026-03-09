/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#include "audio_buffer.h"

AudioBuffer::AudioBuffer(size_t maxBlockSize) {
    if(maxBlockSize) m_resBuffSize = maxBlockSize;
    if(maxBlockSize) m_maxBlockSize = maxBlockSize;
}

AudioBuffer::~AudioBuffer() {
    // m_buffer.reset();
}

bool AudioBuffer::setBufsize(size_t mbs) {
    if(mbs < 2 * m_resBuffSize) {
        log_e("not allowed buffer size must be greater than %i", 2 * m_resBuffSize);
        return false;
    }
    m_buffSize = mbs;
    if(!init()) return false;
    return true;
}

size_t AudioBuffer::init() {
    m_buffer.alloc(m_buffSize + m_resBuffSize, "AudioBuffer");
    m_f_init = true;
    resetBuffer();
    return m_buffSize;
}

void AudioBuffer::changeMaxBlockSize(uint16_t mbs) {
    m_maxBlockSize = mbs;
    return;
}

size_t AudioBuffer::freeSpace() {
    if(m_readPtr == m_writePtr) {
        if(m_f_isEmpty == true) m_freeSpace = m_buffSize;
        else m_freeSpace = 0;
    }
    if(m_readPtr < m_writePtr) {
        m_freeSpace = (m_endPtr - m_writePtr) + (m_readPtr - m_buffer.get());
    }
    if(m_readPtr > m_writePtr) {
        m_freeSpace = m_readPtr - m_writePtr;
    }
    return m_freeSpace;
}

size_t AudioBuffer::writeSpace() {
    if(m_readPtr == m_writePtr) {
        if(m_f_isEmpty == true) m_writeSpace = m_endPtr - m_writePtr;
        else m_writeSpace = 0;
    }
    if(m_readPtr < m_writePtr) {
        m_writeSpace = m_endPtr - m_writePtr;
    }
    if(m_readPtr > m_writePtr) {
        m_writeSpace = m_readPtr - m_writePtr;
    }
    return m_writeSpace;
}

size_t AudioBuffer::bufferFilled() {
    if(m_readPtr == m_writePtr) {
        if(m_f_isEmpty == true) m_dataLength = 0;
        else m_dataLength = m_buffSize;
    }
    if(m_readPtr < m_writePtr) {
        m_dataLength = m_writePtr - m_readPtr;
    }
    if(m_readPtr > m_writePtr) {
        m_dataLength = (m_endPtr - m_readPtr) + (m_writePtr - m_buffer.get());
    }
    return m_dataLength;
}

size_t AudioBuffer::getMaxAvailableBytes() {
    if(m_readPtr == m_writePtr) {
    //   if(m_f_start)m_dataLength = 0;
        if(m_f_isEmpty == true) m_dataLength = 0;
        else m_dataLength = (m_endPtr - m_readPtr);
    }
    if(m_readPtr < m_writePtr) {
        m_dataLength = m_writePtr - m_readPtr;
    }
    if(m_readPtr > m_writePtr) {
        m_dataLength = (m_endPtr - m_readPtr);
    }
    return m_dataLength;
}

void AudioBuffer::bytesWritten(size_t bw) {
    if(!bw) return;
    m_writePtr += bw;
    if(m_writePtr == m_endPtr) { m_writePtr = m_buffer.get(); }
    if(m_writePtr > m_endPtr) log_e("AudioBuffer: m_writePtr %p > m_endPtr %p", m_writePtr, m_endPtr);
    m_f_isEmpty = false;
}

void AudioBuffer::bytesWasRead(size_t br) {
    if(!br) return;
    m_readPtr += br;
    if(m_readPtr >= m_endPtr) {
        size_t tmp = m_readPtr - m_endPtr;
        m_readPtr = m_buffer.get() + tmp;
    }
    if(m_readPtr == m_writePtr) m_f_isEmpty = true;
}

uint8_t* AudioBuffer::getReadPtr() {
    int32_t len = m_endPtr - m_readPtr;
    if(len < m_maxBlockSize) {                            // be sure the last frame is completed
        memcpy(m_endPtr, m_buffer.get(), m_maxBlockSize - (len)); // cpy from m_buffer to m_endPtr with len
    }
    return m_readPtr;
}

void AudioBuffer::resetBuffer() {
    m_writePtr = m_buffer.get();
    m_readPtr = m_buffer.get();
    m_endPtr = m_buffer.get() + m_buffSize;
    m_f_isEmpty = true;
}

uint32_t AudioBuffer::getWritePos() { 
    return m_writePtr - m_buffer.get(); 
}

uint32_t AudioBuffer::getReadPos() { 
    return m_readPtr - m_buffer.get(); 
}

#endif