#ifndef MJPEGIO_HPP
#define MJPEGIO_HPP

#include "resourcefilemanager.hpp"

struct Frame {
    unsigned char* frameDataLoc;
    size_t frameLen;
};

struct Mjpeg {
    std::vector<Frame> frames;
    unsigned char* videoData;
};

class MjpegIO {
public:
    MjpegIO(ResourceFileManager* resourceFileManager);
    void saveMjpeg(std::string& resourceName, BinaryResource b64Data);
    Mjpeg loadMjpeg(std::string& resourceName);
    void freeMjpeg(const Mjpeg& mjpeg);
private: 
    ResourceFileManager* _resourceFileManager;
    std::string _getMetaName(std::string& resourceName);
};

#endif // MJPEGIO_HPP