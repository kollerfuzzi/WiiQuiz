#include "mjpegplayer.hpp"
#include <grrlib.h>
#include "magic_enum.hpp"
#include "mem.hpp"
#include "mjpegio.hpp"
#include "bsod.hpp"

MJpegPlayer::MJpegPlayer(Video video, ResourceFileManager* fileManager){
    _video = video;
    _fileManager = fileManager;
    _currentFrameBuffer = BinaryChunk(nullptr, 0);
    _audioData = BinaryChunk(nullptr, 0);
}

MJpegPlayer::MJpegPlayer(Video video, Audio audio, ResourceFileManager *fileManager) {
    _video = video;
    _fileManager = fileManager;
    _audio = audio;
    _playAudio = true;
    _currentFrameBuffer = BinaryChunk(nullptr, 0);
    _audioData = BinaryChunk(nullptr, 0);
}

MJpegPlayer::~MJpegPlayer(){
    _cleanup();
}

void MJpegPlayer::update(Clock &clock) {
    if (!_isInitialized) {
        _init();
        _isInitialized = true;
    }
    if (_currentFrame >= _mjpeg.frames.size()) {
        _isDone = true;
        if (_currentFrameImg != nullptr) {
            GRRLIB_FreeTexture(_currentFrameImg);
            _currentFrameImg = nullptr;
        }
        return;
    }
    Frame current = _mjpeg.frames[_currentFrame];
    if (_videoStream->getStreamPos() != 0) {
        GRRLIB_FreeTexture(_currentFrameImg);
        _currentFrameImg = nullptr;
    }

    if (_videoStream->getStreamPos() < current.frameStart) {
        _videoStream->advance(_currentFrameBuffer, current.frameStart - _videoStream->getStreamPos());
    }
    size_t frameSize = current.frameEnd - current.frameStart;
    if (frameSize > _frameBufferSize) {
        BSOD::raise("Frame buffer size exceeded");
    }
    _videoStream->read(BinaryChunk(_currentFrameBuffer.data, frameSize));    
    _currentFrameImg = GRRLIB_LoadTextureJPGEx(_currentFrameBuffer.data, frameSize);
    _currentFrame++;
}

void MJpegPlayer::render() {
    // x, y
    if (_currentFrameImg != nullptr) {
        GRRLIB_DrawImg(0, 0, _currentFrameImg, 0, 1.2, 1.2, RGBA(0xff, 0xff, 0xff, 0xff));
    }
}

bool MJpegPlayer::isDone() {
    return _isDone;
}

void MJpegPlayer::reset() {
    _cleanup();
}

void MJpegPlayer::_init() {
    unsigned char* currentFrameBuffer = (unsigned char*) Mem::alloc(_frameBufferSize);
    _currentFrameBuffer = BinaryChunk(currentFrameBuffer, _frameBufferSize);
    _currentFrame = 0;
    _isDone = false;
    _currentFrameImg = nullptr;
    _loadMjpegStream();
    _loadAudio(); 
    MP3Player_Stop();
    MP3Player_PlayBuffer(_audioData.data, _audioData.size, nullptr);
}

void MJpegPlayer::_loadMjpegStream() {
    MjpegIO mjpegio(_fileManager);

    auto enumNameView = magic_enum::enum_name(_video);
    std::string enumName(enumNameView);

    _mjpeg = mjpegio.loadMjpegMeta(enumName);
    _videoStream = _fileManager->loadResourceStream(enumName);
}

void MJpegPlayer::_loadAudio() {
    auto enumNameView = magic_enum::enum_name(_audio);
    std::string enumName(enumNameView);
    _audioData = _fileManager->loadResource(enumName);
}

void MJpegPlayer::_cleanup() {
    if (_videoStream != nullptr) {
        delete _videoStream;
        _videoStream = nullptr;
    }
    if (_currentFrameImg != nullptr) {
        GRRLIB_FreeTexture(_currentFrameImg);
        _currentFrameImg = nullptr;
    }
    if (_currentFrameBuffer.data != nullptr) {
        Mem::mfree(_currentFrameBuffer.data);
        _currentFrameBuffer = BinaryChunk(nullptr, 0);
    }
    /*if (_audioData.data != nullptr) {
        Mem::mfree(_audioData.data);
        _audioData = BinaryChunk(nullptr, 0);
    }*/
    _isInitialized = false;
}
