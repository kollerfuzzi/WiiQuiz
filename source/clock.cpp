#include "clock.hpp"

Clock::Clock() {
    gettimeofday(&_lastTime, NULL);
}

void Clock::tick() {
    timeval now;
    gettimeofday(&now, NULL);
    this->_timeElapsedMicros = (now.tv_sec - this->_lastTime.tv_sec) * 1000000
                               + now.tv_usec - this->_lastTime.tv_usec;
    this->_lastTime = now;
}

int Clock::timeElapsedMicros() const {
    return this->_timeElapsedMicros;
}

float Clock::timeElapsedMillis() const {
    return static_cast<float>(this->_timeElapsedMicros) / 1000;
}

int Clock::timeElapsedMillisInt() const {
    return this->_timeElapsedMicros / 1000;
}

int Clock::currentFPS() const {
    double fps = 1000.0 / this->timeElapsedMillis();
    return static_cast<int>(fps + 0.5);
}
