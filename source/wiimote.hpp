#ifndef WIIMOTE_HPP
#define WIIMOTE_HPP

#include <wiiuse/wpad.h>
#include <vector>
#include <algorithm>
#include "resources.hpp"
#include "grrlib.h"

enum Remote {
    R1 = 0,
    R2 = 1,
    R3 = 2,
    R4 = 3
};

enum Button {
    UP = WPAD_BUTTON_UP,
    DOWN = WPAD_BUTTON_DOWN,
    LEFT = WPAD_BUTTON_LEFT,
    RIGHT = WPAD_BUTTON_RIGHT,
    PLUS = WPAD_BUTTON_PLUS,
    HOME = WPAD_BUTTON_HOME,
    MINUS = WPAD_BUTTON_MINUS,
    ONE = WPAD_BUTTON_1,
    TWO = WPAD_BUTTON_2,
    A = WPAD_BUTTON_A,
    B = WPAD_BUTTON_B
};

struct Pointer {
    bool onScreen;
    float xPos;
    float yPos;
};

namespace WiiMote {
    void init();
    void update();
    bool buttonPressed(Remote remote, Button button);
    std::vector<Button> buttonsPressed(Remote remote);
    bool buttonReleased(Remote remote, Button button);
    Pointer getPointerPosition(Remote remote);
    void drawPointer(Resources* resources, Remote remote);
}

#endif // WIIMOTE_HPP
