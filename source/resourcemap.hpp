#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include "c64font.hpp"
#include "quizbg.hpp"
#include "text_done.hpp"
#include "text_letter.hpp"
#include "evan_mm.hpp"

enum Font {
    C64FONT
};

enum Texture {
    QUIZ_BG
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
