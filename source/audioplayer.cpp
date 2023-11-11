#include "audioplayer.hpp"

void AudioPlayer::init() {
    ASND_Init();
    MP3Player_Init();
}

void AudioPlayer::play(Audio audio, Resources* resources) {
    if (!MP3Player_IsPlaying()) {
        MP3Player_PlayBuffer(resources->get(audio).data,
                             resources->get(audio).size,
                             NULL);
    }
}

void AudioPlayer::stop() {
    MP3Player_Stop();
}

bool AudioPlayer::isPlaying() {
    return MP3Player_IsPlaying();
}
