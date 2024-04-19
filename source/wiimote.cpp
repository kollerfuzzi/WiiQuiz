#include "wiimote.hpp"


void WiiMote::init() {
    WPAD_Init();
    WPAD_SetVRes(WPAD_CHAN_ALL, 640, 480);
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
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

std::vector<Button> WiiMote::buttonsPressed(Remote remote) {
    std::vector<Button> allButtons;
    allButtons.push_back(Button::UP);
    allButtons.push_back(Button::DOWN);
    allButtons.push_back(Button::LEFT);
    allButtons.push_back(Button::RIGHT);
    allButtons.push_back(Button::ONE);
    allButtons.push_back(Button::TWO);
    allButtons.push_back(Button::A);
    allButtons.push_back(Button::B);

    std::vector<Button> pressedButtons;

    for (Button btn : allButtons) {
        if (WiiMote::buttonPressed(remote, btn)) {
            pressedButtons.push_back(btn);
        }
    }

    return pressedButtons;
}

Pointer WiiMote::getPointerPosition(Remote remote) {
    WPADData* data = WPAD_Data(remote);
    struct Pointer ptrData = { (bool) data->ir.valid, data->ir.x, data->ir.y };
    return ptrData;
}

void WiiMote::drawPointer(GRRLIB_texImg* ptrImg, Remote remote) {
    Pointer ptr = WiiMote::getPointerPosition(remote);
    if (ptr.onScreen) {
        GRRLIB_DrawImg(ptr.xPos, ptr.yPos, ptrImg, 0, 1, 1, RGBA(0xff, 0xff, 0xff, 0xff));
    }
}
