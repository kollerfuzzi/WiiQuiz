#include "resourcefilemanager.hpp"
#include "json.hpp"
#include "bsod.hpp"
#include "mem.hpp"

ResourceFileManager::ResourceFileManager() {
    init();
}

void ResourceFileManager::init() {
    if (!fatInitDefault()) {
        BSOD::raise("FAT init failed");
    }
}

void ResourceFileManager::saveResource(std::string& resourceName, BinaryChunk content) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == NULL) {
        std::string err("File read failed ");
        err += fileName;
        BSOD::raise(err);
    }
    fwrite(content.data, 1, content.size, f);
    fclose(f);
}

void ResourceFileManager::saveResourceStream(std::string &resourceName, InputStream* stream) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == nullptr) {
        std::string err("File read failed ");
        err += fileName;
        BSOD::raise(err);
    }
    do {
        BinaryChunk part = stream->read(16384);
        fwrite(part.data, 1, part.size, f);
        Mem::mfree(part.data);
    } while (!stream->isEOF());
    delete stream;
    fclose(f);
}

std::string ResourceFileManager::loadIpAddressFromConfig() {
    std::string ipAddress = "192.168.56.211";
    std::string configFileName = "config.json";
    //BinaryChunk configBin = loadResource(configFileName);
    //if (configBin.data == nullptr) {
    //    return ipAddress;
    //}
    //std::string configStr = (char const*) configBin.data;
    //nlohmann::json configJson = nlohmann::json::parse(configStr);
    //ipAddress = configJson["ipAddress"];
    //freeResource(configBin);
    return ipAddress;
}

BinaryChunk ResourceFileManager::loadResource(std::string& resourceName) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "rb");

    if (f == nullptr) {
        return BinaryChunk { nullptr, 0 };
    } else {
        std::vector<unsigned char> content;
        unsigned char buffer[128];

        while(true) {
            size_t bytes_read = fread(buffer, 1, sizeof(buffer), f);
            if (bytes_read <= 0) {
                break;
            }
            for (size_t i = 0; i < bytes_read; ++i) {
                content.push_back(buffer[i]);
            }
        }

        unsigned char* bytes = (unsigned char*)Mem::alloc(content.size());
        std::copy(content.begin(), content.end(), bytes);
        fclose(f);
        return BinaryChunk(bytes, content.size());
    }
}

nlohmann::json ResourceFileManager::loadResourceJson(std::string &resourceName) {
    BinaryChunk configBin = loadResource(resourceName);
    if (configBin.data == nullptr) {
        BSOD::raise("json file not found");
    }
    std::string configStr = (char const*) configBin.data;
    nlohmann::json configJson = nlohmann::json::parse(configStr);
    Mem::mfree(configBin.data);
    return configJson;
}

InputStream *ResourceFileManager::loadResourceStream(std::string &resourceName) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "rb");
    
    if (f == nullptr) {
        BSOD::raise("resource stream could not be loaded");
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    return new FileInputStream(f, size); 
}

void ResourceFileManager::freeResource(const BinaryChunk& resource) {
    Mem::mfree(resource.data);
}

std::string ResourceFileManager::_resourceNameToFileName(std::string &resourceName) {
    std::string fileName("wiiquiz/");
    fileName += resourceName;
    if (resourceName.find(".") == std::string::npos) {
        fileName += ".bin";
    }
    return fileName;

}

FileInputStream::FileInputStream(FILE* file, size_t fileSize) {
    _file = file;
    _maxSize = fileSize;
}

FileInputStream::~FileInputStream() {
    close();
}

BinaryChunk FileInputStream::read(size_t maxLen) {
    unsigned char* buffer = (unsigned char*) Mem::alloc(maxLen);

    // read til max len or eof
    size_t bufferPos = 0;
    size_t attemptReadSize = 16384;
    while (bufferPos < maxLen) {
        if (bufferPos + attemptReadSize >= maxLen) {
            attemptReadSize = maxLen - bufferPos;
        }
        size_t bytesRead = fread(buffer + bufferPos, 1, attemptReadSize, _file);
        bufferPos += bytesRead;
    
        if (bytesRead <= 0) {
            fclose(_file);
            _open = false;
        }
    }

    if (bufferPos < maxLen / 2 && bufferPos > 0) {
        BSOD::raise("bytesRead < maxLen");
        unsigned char* memSaveBuffer = (unsigned char*) Mem::alloc(bufferPos);
        memcpy(memSaveBuffer, buffer, bufferPos);
        Mem::mfree(buffer);
        buffer = memSaveBuffer;
    }
    _streamPos += bufferPos;
    return BinaryChunk(buffer, bufferPos);
}

size_t FileInputStream::getMaxSize() {
    return _maxSize;
}

void FileInputStream::close() {
    if (_open) {
        fclose(_file);
    }
}
