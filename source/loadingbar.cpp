#include "loadingbar.hpp"

timeval LoadingBar::_lastRender = {0, 0};
int LoadingBar::_ticks = 0;
int LoadingBar::_currentTick = 0;

void LoadingBar::setTicks(int ticks) {
    gettimeofday(&_lastRender, NULL);
    LoadingBar::_ticks = ticks;
    LoadingBar::_currentTick = 0;
}

void LoadingBar::tick(GRRLIB_ttfFont* font) {
    LoadingBar::_currentTick++;
    float percent = ((f32) LoadingBar::_currentTick / (f32) LoadingBar::_ticks) * 100;
    if (percent > 100) {
        percent = 100;
    }

    timeval now;
    gettimeofday(&now, NULL);
    long timeElapsedMillis = (now.tv_sec - LoadingBar::_lastRender.tv_sec) * 1000
                               + (now.tv_usec - LoadingBar::_lastRender.tv_usec) / 1000;
    if (timeElapsedMillis < 50) {
        return;
    }
    LoadingBar::_lastRender = now;
    GRRLIB_SetBackgroundColour(0, 0x00, 0, 0xff);
    GRRLIB_3dMode(0.1, 1000, 45, 0, 1);
    GRRLIB_SetLightAmbient(0xffffffff);
    for (int i = 0; i < percent; i++) {
        GRRLIB_ObjectView(-80 + i * 1.6f, 0, -200.f, 0, 0, 0, 1, 1, 1);
        GRRLIB_DrawCube(10, true, 0xaaaaaaff);
    }

    for (int i = 0; i < 100; i++) {
        GRRLIB_ObjectView(-80 + i * 1.6f, 0, -200.1f, 0, 0, 0, 1.4, 1.4, 1);
        GRRLIB_DrawCube(10, true, 0x000077ff);
    }

    GRRLIB_2dMode();
    GRRLIB_PrintfTTF(75, 150, font, "Loading...", 20, RGBA(150, 150, 255, 255));

    GRRLIB_Render();
}

