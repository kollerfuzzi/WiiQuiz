#ifndef RESOURCEFILEMANAGER_HPP
#define RESOURCEFILEMANAGER_HPP

#include <fat.h>
#include <sys/stat.h>
#include "base64.hpp"

struct BinaryResource {
    unsigned char* data;
    size_t size;
    BinaryResource() {

    }

    BinaryResource(unsigned char* _data, size_t _size) {
        data = _data;
        size = _size;
    }
};

class ResourceFileManager {
public:
    ResourceFileManager();
    void init();
    void saveResource(std::string& resourceName, std::string& contentBase64);
    void saveResourcePlain(std::string& resourceName, std::string& contentPlain);
    BinaryResource loadResource(std::string& resourceName);
    void freeResource(const BinaryResource& resource);
private:
    std::string _resourceNameToFileName(std::string& resourceName);
};

#endif // RESOURCEFILEMANAGER_HPP
