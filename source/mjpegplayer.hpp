#ifndef MJPEGPLAYER_HPP
#define MJPEGPLAYER_HPP

#include "renderable.hpp"
#include "resourcefilemanager.hpp"
#include "mjpeg.hpp"
#include "resourcemap.hpp"
#include "asndlib.h"
#include "mp3player.h"

class MJpegPlayer : public Renderable {
public:
    MJpegPlayer(Video video, ResourceFileManager* fileManager);
    MJpegPlayer(Video video, Audio audio, ResourceFileManager* fileManager);
    ~MJpegPlayer();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
private:
    void _init();
    void _loadMjpegStream();
    void _loadAudio();
    void _cleanup();
    ResourceFileManager* _fileManager = nullptr;
    InputStream* _videoStream = nullptr;
    BinaryChunk _currentFrameBuffer;
    GRRLIB_texImg* _currentFrameImg = nullptr;
    Video _video;
    Audio _audio;
    BinaryChunk _audioData;
    bool _playAudio = false;
    Mjpeg _mjpeg;
    size_t _currentFrame = 0;
    size_t _frameBufferSize = 1048576;
    bool _isInitialized = false;
    bool _isDone = false;
};

#endif // MJPEGPLAYER_HPP