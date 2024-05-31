#include "resourcemap.hpp"

std::map<Font, std::string> FONT_PATHS = {
    {Font::DEFAULT_FONT, "fonts/NotoSansMono.ttf"}
};

std::map<Texture, std::string> TEXTURE_PATHS = {
    {Texture::CURSOR, "textures/cursor.png"},
    {Texture::MENU_BUTTON, "textures/button.png"},
    {Texture::START_BG, "textures/start.png"},
    {Texture::QUIZ_BG, "textures/quizbg.png"},
    {Texture::SCOREBOARD_BG, "textures/scoreboard.png"},
    {Texture::BTN_A, "textures/buttons/a.png"},
    {Texture::BTN_DPAD, "textures/buttons/dpad.png"},
    {Texture::BTN_DPAD_UP, "textures/buttons/dpad_up.png"},
    {Texture::BTN_DPAD_RIGHT, "textures/buttons/dpad_right.png"},
    {Texture::BTN_DPAD_DOWN, "textures/buttons/dpad_down.png"},
    {Texture::BTN_DPAD_RIGHT, "textures/buttons/dpad_right.png"},
    {Texture::BTN_ONE, "textures/buttons/one.png"},
    {Texture::BTN_TWO, "textures/buttons/two.png"},
    {Texture::RYTHM_BAR, "textures/rythm_bar.png"},
};

std::map<Audio, std::string> AUDIO_PATHS = {
    {Audio::TEXT_LETTER, "audio/text_letter.mp3"},
    {Audio::TEXT_DONE, "audio/text_done.mp3"},
    {Audio::EVAN_MM, "audio/evan_mm.mp3"},
    {Audio::GETTING_READY, "audio/getting_ready.mp3"},
};

std::map<Video, std::string> VIDEO_PATHS = {

};