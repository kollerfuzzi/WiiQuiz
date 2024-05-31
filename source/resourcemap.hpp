#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include <string>
#include <map>

enum Font {
    DEFAULT_FONT
};

extern std::map<Font, std::string> FONT_PATHS;

enum Texture {
    CURSOR,
    MENU_BUTTON,
    START_BG,
    QUIZ_BG,
    SCOREBOARD_BG,
    BTN_A,
    BTN_DPAD,
    BTN_DPAD_UP,
    BTN_DPAD_LEFT,
    BTN_DPAD_DOWN,
    BTN_DPAD_RIGHT,
    BTN_ONE,
    BTN_TWO,
    RYTHM_BAR,
    QUALLE,
    LINK_BOLERO,
    ANIME
};

extern std::map<Texture, std::string> TEXTURE_PATHS;

enum Audio {
    EVAN_MM,
    TEXT_LETTER,
    TEXT_DONE,
    GETTING_READY,
    DISCOQUALLEN,
    BOLERO_OF_FIRE,
    ROCKEFELLER_ST,
    TP_TRAILER_AUDIO
};


extern std::map<Audio, std::string> AUDIO_PATHS;

enum Video {
    Z_TRAILER,
    TP_TRAILER
};

extern std::map<Video, std::string> VIDEO_PATHS;

#endif // RESOURCEMAP_HPP
