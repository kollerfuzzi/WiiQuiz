#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "clock.hpp"

class Renderable {
public:
    Renderable();
    virtual ~Renderable() = 0;
    virtual void update(const Clock& clock) = 0;
    virtual void render() = 0;
private:

};

#endif // RENDERABLE_HPP
