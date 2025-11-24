
#ifndef _TIMER_H
#define _TIMER_H

#include <functional>
#include <cstdint>

class Timer {
public:

    virtual bool Start(uint32_t interval_ms, std::function<void()> callback_function, bool once=false) = 0;
    virtual bool Stop() = 0;


};

#endif //_TIMER_H