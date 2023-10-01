#ifndef RESOURCEMAP_HPP
#define RESOURCEMAP_HPP

#include "c64font.hpp"
#include "quizbg.hpp"

enum Font {
    C64FONT
};

enum Texture {
    QUIZ_BG
};

struct FontDef {
    Font font;
    unsigned char* fontRef;
    unsigned int fontLen;
};

extern FontDef FONT_DEFINITIONS[];

struct TextureDef {
    Texture texture;
    unsigned char* textureRef;
};

extern TextureDef TEXTURE_DEFINITIONS[];

#endif // RESOURCEMAP_HPP
