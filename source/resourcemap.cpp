#include "resourcemap.hpp"


FontDef FONT_DEFINITIONS[] = {
    {Font::C64FONT, "fonts/c64font.ttf"}
};

TextureDef TEXTURE_DEFINITIONS[] = {
    {Texture::START_BG, "textures/start.png"},
    {Texture::QUIZ_BG, "textures/quizbg.png"},
    {Texture::SCOREBOARD_BG, "textures/scoreboard.png"},
    {Texture::BTN_A, "textures/buttons/a.png"},
    {Texture::BTN_DPAD, "textures/buttons/dpad.png"},
    {Texture::BTN_ONE, "textures/buttons/one.png"},
    {Texture::BTN_TWO, "textures/buttons/two.png"},
    {Texture::RYTHM_BAR, "textures/rythm_bar.png"},
    {Texture::QUALLE, "textures/qualle.png"},
    {Texture::LINK_BOLERO, "textures/link_bolero.png"}
};


AudioDef AUDIO_DEFINITIONS[] = {
    {Audio::TEXT_LETTER, "audio/text_letter.mp3"},
    {Audio::TEXT_DONE, "audio/text_done.mp3"},
    {Audio::EVAN_MM, "audio/evan_mm.mp3"},
    {Audio::GETTING_READY, "audio/getting_ready.mp3"},
    {Audio::DISCOQUALLEN, "audio/discoquallen.mp3"},
    {Audio::BOLERO_OF_FIRE, "audio/bolero_of_fire.mp3"}
};
