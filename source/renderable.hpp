#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "clock.hpp"
#include "wiimote.hpp"
#include "renderable.hpp"
#include "screendebug.hpp"

class Renderable {
public:
    Renderable();
    virtual ~Renderable() = 0;
    void runUntilDone(Clock& frameClock, GRRLIB_texImg* ptrImg);
    virtual void update(Clock& clock) = 0;
    virtual void render() = 0;
    virtual bool isDone() = 0;
    virtual void reset() = 0;
};

#endif // RENDERABLE_HPP
