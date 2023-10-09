#include "resourcemap.hpp"


FontDef FONT_DEFINITIONS[] = {
    {Font::C64FONT, c64font_ttf, c64font_ttf_len}
};

TextureDef TEXTURE_DEFINITIONS[] = {
    {Texture::QUIZ_BG, quizbg_png}
};


AudioDef AUDIO_DEFINITIONS[] = {
    {Audio::TEXT_LETTER, text_letter_mp3, text_letter_mp3_len},
    {Audio::TEXT_DONE, text_done_mp3, text_done_mp3_len},
    {Audio::EVAN_MM, evan_mm_mp3, evan_mm_mp3_len}
};
