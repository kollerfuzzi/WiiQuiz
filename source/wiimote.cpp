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
