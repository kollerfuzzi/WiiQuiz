#ifndef RESOURCEFILEMANAGER_HPP
#define RESOURCEFILEMANAGER_HPP

#include <fat.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include "io_stream.hpp"
#include "json.hpp"

class FileInputStream : public InputStream {
public:
    FileInputStream(FILE* file, size_t fileSize);
    ~FileInputStream();
    size_t read(BinaryChunk buffer);
    size_t getMaxSize();
    void close();
protected:
    FILE* _file;
    size_t _maxSize = 0;
};

class ResourceFileManager {
public:
    ResourceFileManager();
    void init();
    void saveResource(std::string& resourceName, BinaryChunk content);
    void saveResourceStream(std::string& resourceName, InputStream* stream);
    std::string loadIpAddressFromConfig();
    BinaryChunk loadResource(std::string& resourceName);
    nlohmann::json loadResourceJson(std::string& resourceName);
    InputStream* loadResourceStream(std::string& resourceName);
    void freeResource(const BinaryChunk& resource);
private:
    std::string _resourceNameToFileName(std::string& resourceName);
};

#endif // RESOURCEFILEMANAGER_HPP
