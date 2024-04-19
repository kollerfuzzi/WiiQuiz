#ifndef MJPEGPLAYER_HPP
#define MJPEGPLAYER_HPP

#include "renderable.hpp"
#include "resourcefilemanager.hpp"
#include "mjpeg.hpp"
#include "resourcemap.hpp"

class MJpegPlayer : public Renderable {
public:
    MJpegPlayer(Video video, ResourceFileManager* fileManager);
    ~MJpegPlayer();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
private:
    void _init();
    void _loadMjpegStream();
    void _cleanup();
    ResourceFileManager* _fileManager;
    InputStream* _videoStream;
    GRRLIB_texImg* _currentFrameImg = nullptr;
    Video _video;
    Mjpeg _mjpeg;
    size_t _currentFrame = 0;
    bool _isInitialized = false;
    bool _isDone = false;
};

#endif // MJPEGPLAYER_HPP