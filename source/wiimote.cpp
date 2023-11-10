#include "wiimote.hpp"


void WiiMote::init() {
    WPAD_Init();
}

void WiiMote::update() {
    WPAD_ScanPads();
}

bool WiiMote::buttonPressed(Remote remote, Button button) {
    return WPAD_ButtonsDown(remote) & button;
}

bool WiiMote::buttonReleased(Remote remote, Button button) {
    return WPAD_ButtonsUp(remote) & button;
}
