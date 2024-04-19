#ifndef SWINGINGLIGHTS_HPP
#define SWINGINGLIGHTS_HPP

#include "renderable.hpp"

class SwingingLights : public Renderable {
public:
    SwingingLights();
    void update(Clock &clock);
    void render();
    bool isDone();
    void reset();
private:
    f32 _lightx = 0.0f;
};

#endif // SWINGINGLIGHTS_HPP
