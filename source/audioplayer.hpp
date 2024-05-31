#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP


#include "resources.hpp"
#include "asndlib.h"
#include "mp3player.h"

namespace AudioPlayer {
    void init();
    void play(Audio audio, Resources* resources);
    void play(std::string audioPath, Resources* resources);
    bool isPlaying();
    void stop();
}

#endif // AUDIOPLAYER_HPP


