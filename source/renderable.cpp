#include "renderable.hpp"

Renderable::Renderable() {}

void Renderable::runUntilDone(Clock& frameClock, GRRLIB_texImg* ptrImg) {
    while (!isDone()) {
        frameClock.tick();
        WiiMote::update();
        GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

        if (WiiMote::buttonPressed(Remote::R1, Button::HOME)) {
            return;
        }

        update(frameClock);
        render();

        WiiMote::drawPointer(ptrImg, Remote::R1);

        ScreenDebug::render();
        GRRLIB_Render();
    }
    reset();
}

Renderable::~Renderable() {

}
