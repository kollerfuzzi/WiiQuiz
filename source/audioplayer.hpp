#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP


#include "resources.hpp"
#include "asndlib.h"
#include "mp3player.h"

class AudioPlayer {
public:
    AudioPlayer();
    static void init(Resources* resources);
    static void destroy();
    static void play(Audio audio);
private:
    static Resources _resources;
};

#endif // AUDIOPLAYER_HPP
/*
// init
    ASND_Init();
    MP3Player_Init();
// run
    if (!MP3Player_IsPlaying()) {
        MP3Player_PlayBuffer(resources->get(Audio::GETTING_READY).audioRef,
                             resources->get(Audio::GETTING_READY).audioLen,
                             NULL);
    }

*/

/*
class ScreenDebug {
public:
    ~ScreenDebug();
    static void init(Resources* resources);
    static void destroy();
    static ScreenDebug* instance();
    static void printLn(std::string text);
    static void print(std::vector<std::string>& lines);
    static void render();
    static void clear();
private:
    void _printLn(std::string text);
    void _render();
    void _clear();
    ScreenDebug(Resources* resources);
    static ScreenDebug* _instance;
    std::string _text;
    TextBox* _textbox = nullptr;
    Resources* _resources;
};*/
