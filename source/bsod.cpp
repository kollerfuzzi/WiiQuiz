#include "bsod.hpp"

#include "screendebug.hpp"
#include "wiimote.hpp"
#include "grrlib.h"

void BSOD::raise(std::string error, int code) {
    ScreenDebug::clear();
    ScreenDebug::setColor(RGBA(255, 255, 255, 255));
    ScreenDebug::printLn("\nAn error has occured.\n\n"
                         "To continue: \n"
                         "Press <HOME> to return\n"
                         "to Homebrew Channel\n\n"
                         "Error:");
    ScreenDebug::printLn(error);
    std::string errCode("CODE: ");
    errCode += std::to_string(code);
    ScreenDebug::printLn(errCode);

    while(!WiiMote::buttonPressed(Remote::R1, Button::HOME)) {
        GRRLIB_SetBackgroundColour(0x00, 0x00, 0xAA, 0xFF);
        WiiMote::update();
        ScreenDebug::render();
        GRRLIB_Render();
    }
    exit(0);
}

void BSOD::raise(std::string error) {
    BSOD::raise(error, 0xFF);
}
