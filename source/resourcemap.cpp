#include "resourcemap.hpp"


FontDef FONT_DEFINITIONS[] = {
    {Font::C64FONT, c64font_ttf, c64font_ttf_len}
};

TextureDef TEXTURE_DEFINITIONS[] = {
    {Texture::START_BG, start_png},
    {Texture::QUIZ_BG, quizbg_png},
    {Texture::SCOREBOARD_BG, scoreboard_png},
    {Texture::BTN_A, a_png},
    {Texture::BTN_DPAD, dpad_png},
    {Texture::BTN_ONE, one_png},
    {Texture::BTN_TWO, two_png}
};


AudioDef AUDIO_DEFINITIONS[] = {
    {Audio::TEXT_LETTER, text_letter_mp3, text_letter_mp3_len},
    {Audio::TEXT_DONE, text_done_mp3, text_done_mp3_len},
    {Audio::EVAN_MM, evan_mm_mp3, evan_mm_mp3_len},
    {Audio::GETTING_READY, getting_ready_mp3, getting_ready_mp3_len},
    {Audio::DISCOQUALLEN, discoquallen_mp3, discoquallen_mp3_len},
};
