#ifndef MJPEGPLAYER_HPP
#define MJPEGPLAYER_HPP

#include "renderable.hpp"
#include "resourcefilemanager.hpp"
#include "mjpeg.hpp"
#include "resourcemap.hpp"
#include "asndlib.h"
#include "mp3player.h"

struct AVResource {
    static AVResource of(std::string videoPath, std::string audioPath);
    static AVResource none();
    std::string videoPath;
    std::string audioPath;
    const bool operator==(const AVResource other);
};

/*
You can convert videos to MJPeg with ffmpeg

ffmpeg -i filename.mp4 filename.mp3
 */
class MJpegPlayer : public Renderable {
public:
    MJpegPlayer(AVResource resource, ResourceFileManager* fileManager);
    ~MJpegPlayer();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
private:
    void _init();
    void _loadMjpegStream();
    void _loadAudio();
    void _deleteCurrentFrame();
    void _cleanup();
    ResourceFileManager* _fileManager = nullptr;
    InputStream* _videoStream = nullptr;
    BinaryChunk _currentFrameBuffer = {nullptr, 0};
    GRRLIB_texImg* _currentFrameImg = nullptr;
    AVResource _resource;
    std::string _videoHash;
    std::string _audioHash;
    BinaryChunk _audioData = {nullptr, 0};
    bool _playAudio = false;
    Mjpeg _mjpeg;
    size_t _currentFrame = 0;
    size_t _frameBufferSize = 1048576;
    u32 _timeSinceLastFrameMicros = 0;
    bool _isInitialized = false;
    bool _isDone = false;
};

#endif // MJPEGPLAYER_HPP