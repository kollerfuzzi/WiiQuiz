#include "mjpegplayer.hpp"
#include <grrlib.h>
#include "magic_enum.hpp"
#include "mem.hpp"
#include "mjpegio.hpp"
#include "bsod.hpp"

MJpegPlayer::MJpegPlayer(Video video, ResourceFileManager* fileManager){
    _video = video;
    _fileManager = fileManager;
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
    BinaryChunk resource;
    if (_videoStream->getStreamPos() != 0) {
        GRRLIB_FreeTexture(_currentFrameImg);
        _currentFrameImg = nullptr;
    }

    if (_videoStream->getStreamPos() < current.frameStart) {
        _videoStream->advance(current.frameStart - _videoStream->getStreamPos());
    }
    resource = _videoStream->read(current.frameEnd - current.frameStart);    

    _currentFrameImg = GRRLIB_LoadTextureJPGEx(resource.data, resource.size);
    Mem::mfree(resource.data);
    
    _currentFrame++;
}

void MJpegPlayer::render() {
    // x, y
    if (_currentFrameImg != nullptr) {
        GRRLIB_DrawImg(0, 0, _currentFrameImg, 0, 1, 1, RGBA(0xff, 0xff, 0xff, 0xff));
    }
}

bool MJpegPlayer::isDone() {
    return _isDone;
}

void MJpegPlayer::reset() {
    _cleanup();
}

void MJpegPlayer::_init() {
    _currentFrame = 0;
    _isDone = false;
    _currentFrameImg = nullptr;
    _loadMjpegStream();
}

void MJpegPlayer::_loadMjpegStream() {
    MjpegIO mjpegio(_fileManager);

    auto enumNameView = magic_enum::enum_name(_video);
    std::string enumName(enumNameView);

    _mjpeg = mjpegio.loadMjpegMeta(enumName);
    _videoStream = _fileManager->loadResourceStream(enumName);
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
    _isInitialized = false;
}
