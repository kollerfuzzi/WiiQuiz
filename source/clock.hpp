#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "sys/time.h"
#include <cstdint>

class Clock {
public:
    Clock();
    void tick();
    int32_t timeElapsedMicros() const;
    float timeElapsedMillis() const;
    int32_t timeElapsedMillisInt() const;
    int32_t currentFPS() const;
private:
    timeval _lastTime;
    int32_t _timeElapsedMicros;
};

#endif // CLOCK_HPP
