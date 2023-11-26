#include "swinginglights.hpp"
#include <cmath>

SwingingLights::SwingingLights() {}

void SwingingLights::update(Clock &clock) {
    _lightx += 0.003f * clock.timeElapsedMillis();
}

void SwingingLights::render() {
    GRRLIB_Camera3dSettings(0.0f,0.0f,3.0f, 0,1,0, 0,0,0);
    GRRLIB_SetLightAmbient(0x404040FF);

    GRRLIB_SetLightSpot(1, (guVector){(f32) (sin(_lightx)*2.5f), 0.8f, 0 },
                        (guVector){(f32) (sin(_lightx)*2.5f), 0.0f, 0.0f },
                        -4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0x0000FFFF);
    GRRLIB_SetLightSpot(2, (guVector){(f32) (-sin(_lightx)*2.5f), 0.8f, 0 },
                        (guVector){(f32) (-sin(_lightx)*2.5f), 0.0f, 0.0f },
                        -4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0xFF0000FF);

    GRRLIB_3dMode(0.1,1000,45,0,1);
    GRRLIB_ObjectView(0,-0.8 ,0 ,-90 ,0 ,0 ,1 ,1 ,1 );
    GRRLIB_DrawTessPanel(6.2f,0.17f,3.7f,0.1f,0,0xFFFFFFFF);

    GRRLIB_2dMode();
}

bool SwingingLights::isDone() {
    return false;
}
