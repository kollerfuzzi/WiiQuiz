#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP


#include "resources.hpp"
#include "asndlib.h"
#include "mp3player.h"

class AudioPlayer {
public:
    static void init();
    static void play(Audio audio, Resources* resources);
    static void play(std::string audioPath, Resources* resources);
    static bool isPlaying();
    static void stop();
};

#endif // AUDIOPLAYER_HPP
