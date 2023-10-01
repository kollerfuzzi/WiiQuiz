#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "sys/time.h"


class Clock
{
public:
    Clock();
    void tick();
    int timeElapsedMicros();
    float timeElapsedMillis();
    int currentFPS();
private:
    timeval _lastTime;
    int _timeElapsedMicros;
};

#endif // CLOCK_HPP
