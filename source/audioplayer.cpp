#include "audioplayer.hpp"

void AudioPlayer::init() {
    ASND_Init();
    MP3Player_Init();
}

void AudioPlayer::play(Audio audio, Resources* resources) {
    AudioPlayer::play(Resources::pathOf(audio), resources);
}

void AudioPlayer::play(std::string audioPath, Resources* resources) {
    if (!MP3Player_IsPlaying()) {
        MP3Player_PlayBuffer(resources->getAudio(audioPath).data,
                             resources->getAudio(audioPath).size,
                             NULL);
    }
}

void AudioPlayer::stop() {
    MP3Player_Stop();
}

bool AudioPlayer::isPlaying() {
    return MP3Player_IsPlaying();
}
