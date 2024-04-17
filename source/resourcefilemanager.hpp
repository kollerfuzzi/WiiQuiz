#ifndef RESOURCEFILEMANAGER_HPP
#define RESOURCEFILEMANAGER_HPP

#include <fat.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include "base64.hpp"
#include "binaryresource.hpp"

class ResourceFileManager {
public:
    ResourceFileManager();
    void init();
    void saveResource(std::string& resourceName, BinaryResource contentBase64);
    void saveResourcePlain(std::string& resourceName, BinaryResource contentPlain);
    std::string loadIpAddressFromConfig();
    BinaryResource loadResource(std::string& resourceName);
    void freeResource(const BinaryResource& resource);
private:
    std::string _resourceNameToFileName(std::string& resourceName);
};

#endif // RESOURCEFILEMANAGER_HPP
