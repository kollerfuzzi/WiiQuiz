#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include "zr_c64font.hpp"
#include "zr_quizbg.hpp"
#include "zr_text_done.hpp"
#include "zr_text_letter.hpp"
#include "zr_evan_mm.hpp"
#include "zr_scoreboard.hpp"
#include "zr_image_test.hpp"
#include "zr_start.hpp"
#include "zr_getting_ready.hpp"

#include "zr_discoquallen.hpp"
#include "zr_btn_a.hpp"
#include "zr_btn_dpad.hpp"
#include "zr_btn_one.hpp"
#include "zr_btn_two.hpp"

enum Font {
    C64FONT
};

enum Texture {
    START_BG,
    QUIZ_BG,
    SCOREBOARD_BG,
    BTN_A,
    BTN_DPAD,
    BTN_ONE,
    BTN_TWO
};

enum Audio {
    TEXT_LETTER,
    TEXT_DONE,
    EVAN_MM,
    GETTING_READY,
    DISCOQUALLEN
};


struct FontDef {
    Font font;
    unsigned char * fontRef;
    unsigned int fontLen;
};

extern FontDef FONT_DEFINITIONS[];

struct TextureDef {
    Texture texture;
    unsigned char * textureRef;
};

extern TextureDef TEXTURE_DEFINITIONS[];

struct AudioDef {
    Audio audio;
    unsigned char * audioRef;
    unsigned int audioLen;
};

extern AudioDef AUDIO_DEFINITIONS[];

#endif // RESOURCEMAP_HPP
