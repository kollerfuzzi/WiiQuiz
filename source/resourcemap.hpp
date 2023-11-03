#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include "zr_c64font.hpp"
#include "zr_quizbg.hpp"
#include "zr_text_done.hpp"
#include "zr_text_letter.hpp"
#include "zr_evan_mm.hpp"
#include "zr_scoreboard.hpp"
#include "zr_image_test.hpp"

enum Font {
    C64FONT
};

enum Texture {
    QUIZ_BG,
    SCOREBOARD_BG
};

enum Audio {
    TEXT_LETTER,
    TEXT_DONE,
    EVAN_MM
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
