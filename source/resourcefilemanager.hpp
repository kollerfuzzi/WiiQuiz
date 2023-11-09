#ifndef RESOURCEFILEMANAGER_HPP
#define RESOURCEFILEMANAGER_HPP

#include <iostream>
#include <fstream>
#include <fat.h>
#include <sys/stat.h>
#include "base64.hpp"

class ResourceFileManager
{
public:
    ResourceFileManager();
    void init();
private:
    void saveResource(std::string& resourceName, std::string& contentBase64);
    unsigned char* loadResource(std::string& resourceName);
    unsigned char* freeResource(unsigned char* resource);
};

#endif // RESOURCEFILEMANAGER_HPP
