#include "mjpegplayer.hpp"
#include <grrlib.h>
#include "magic_enum.hpp"
#include "mem.hpp"
#include "mjpegio.hpp"
#include "bsod.hpp"

MJpegPlayer::MJpegPlayer(std::string videoHash, ResourceFileManager* fileManager){
    _videoHash = videoHash;
    _fileManager = fileManager;
    _currentFrameBuffer = BinaryChunk(nullptr, 0);
    _audioData = BinaryChunk(nullptr, 0);
}

MJpegPlayer::MJpegPlayer(std::string videoHash, std::string audioHash, ResourceFileManager *fileManager) {
    _videoHash = videoHash;
    _fileManager = fileManager;
    _audioHash = audioHash;
    _playAudio = true;
    _currentFrameBuffer = BinaryChunk(nullptr, 0);
    _audioData = BinaryChunk(nullptr, 0);
}

MJpegPlayer::~MJpegPlayer(){
    _cleanup();
}

void MJpegPlayer::update(Clock& clock) {
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
    if (_currentFrameImg != nullptr) {
        GRRLIB_DrawImg(0, 0, _currentFrameImg, 0, 
            (f32) rmode->fbWidth / (f32) _currentFrameImg->w,
            (f32) rmode->xfbHeight / (f32) _currentFrameImg->h, 
            0xffffffff);
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
    _mjpeg = mjpegio.loadMjpegMeta(_videoHash);
    _videoStream = _fileManager->loadResourceStream(_videoHash);
}

void MJpegPlayer::_loadAudio() {
    _audioData = _fileManager->loadResource(_audioHash);
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
    if (_audioData.data != nullptr) {
        Mem::mfree(_audioData.data);
        _audioData = BinaryChunk(nullptr, 0);
    }
    _isInitialized = false;
    _isDone = false;
}

AVResource AVResource::of(std::string mjpegPath, std::string audioPath) {
    AVResource video;
    video.videoPath = mjpegPath;
    video.audioPath = audioPath;
    return video;
}

AVResource AVResource::none() {
    return AVResource::of("", "");
}

const bool AVResource::operator==(const AVResource other) {
    return videoPath == other.videoPath
        && audioPath == other.audioPath;
}
