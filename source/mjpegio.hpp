#ifndef MJPEGIO_HPP
#define MJPEGIO_HPP

#include "resourcefilemanager.hpp"
#include "mjpeg.hpp"

class MjpegIO {
public:
    MjpegIO(ResourceFileManager* resourceFileManager);
    void saveMjpegStream(std::string& resourceName, InputStream* stream);
    Mjpeg loadMjpegMeta(std::string& resourceName);
private: 
    ResourceFileManager* _resourceFileManager;
    std::string _getMetaName(std::string& resourceName);
};

#endif // MJPEGIO_HPP