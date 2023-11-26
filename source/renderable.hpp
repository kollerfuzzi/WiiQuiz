#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "clock.hpp"
#include "wiimote.hpp"
#include "renderable.hpp"
#include "screendebug.hpp"
#include "resources.hpp"

class Renderable {
public:
    Renderable();
    virtual ~Renderable() = 0;
    void runUntilDone(Clock& frameClock, Resources* resources);
    virtual void update(Clock& clock) = 0;
    virtual void render() = 0;
    virtual bool isDone() = 0;
private:

};

#endif // RENDERABLE_HPP
