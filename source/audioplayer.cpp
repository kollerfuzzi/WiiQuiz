#include "audioplayer.hpp"

std::string AudioPlayer::_playingAudio = "";

void AudioPlayer::init() {
    ASND_Init();
    MP3Player_Init();
}

void AudioPlayer::play(Audio audio, Resources* resources) {
    AudioPlayer::play(Resources::pathOf(audio), resources);
}

void AudioPlayer::play(std::string audioPath, Resources* resources) {
    if (!MP3Player_IsPlaying()) {
        AudioPlayer::_playingAudio = audioPath;
        resources->addReserved(_playingAudio);
        MP3Player_PlayBuffer(resources->getAudio(audioPath).data,
                             resources->getAudio(audioPath).size,
                             NULL);
    }
}

void AudioPlayer::stop(Resources* resources) {
    MP3Player_Stop();
    if (!_playingAudio.empty()) {
        resources->removeReserved(_playingAudio);
        AudioPlayer::_playingAudio = "";
    }
}

bool AudioPlayer::isPlaying() {
    return MP3Player_IsPlaying();
}
