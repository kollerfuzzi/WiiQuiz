#ifndef MJPEG_HPP
#define MJPEG_HPP

#include <vector>

struct Frame {
    size_t frameStart;
    size_t frameEnd;
};

struct Mjpeg {
    std::vector<Frame> frames;
};

#endif // MJPEG_HPP