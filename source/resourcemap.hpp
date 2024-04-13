#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include <string>

enum ResourceLocation {
    SERVER,
    BINARY
};

enum Font {
    DEFAULT_FONT
};

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

enum Audio {
    TEXT_LETTER,
    TEXT_DONE,
    EVAN_MM,
    GETTING_READY,
    DISCOQUALLEN,
    BOLERO_OF_FIRE,
    ROCKEFELLER_ST
};


struct FontDef {
    Font font;
    std::string remotePath;
};

extern FontDef FONT_DEFINITIONS[];

struct TextureDef {
    Texture texture;
    std::string remotePath;
};

extern TextureDef TEXTURE_DEFINITIONS[];

struct AudioDef {
    Audio audio;
    std::string remotePath;
};

extern AudioDef AUDIO_DEFINITIONS[];

#endif // RESOURCEMAP_HPP
