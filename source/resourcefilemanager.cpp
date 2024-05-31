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
        std::string err("File write failed ");
        err += fileName;
        BSOD::raise(err);
    }
    fwrite(content.data, 1, content.size, f);
    fclose(f);
}

void ResourceFileManager::saveResourceJson(std::string &resourceName, nlohmann::json json) {
    std::string str = json.dump();
    saveResource(resourceName, BinaryChunk((unsigned char*) str.c_str(), str.size()));
}

void ResourceFileManager::saveResourceStream(std::string &resourceName, InputStream* stream) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == nullptr) {
        std::string err("File write failed ");
        err += fileName;
        BSOD::raise(err);
    }
    BinaryChunk part((unsigned char*) Mem::alloc(16384), 16384);
    do {
        size_t size = stream->read(part);
        fwrite(part.data, 1, size, f);
    } while (!stream->isEOF());
    Mem::mfree(part.data);
    delete stream;
    fclose(f);
}

std::string ResourceFileManager::loadIpAddressFromConfig() {
    std::string ipAddress = "127.0.0.1";
    std::string configFileName = "config.json";
    BinaryChunk configBin = loadResource(configFileName);
    if (configBin.data == nullptr) {
        return ipAddress;
    }
    std::string configStr((char const*) configBin.data, configBin.size);
    nlohmann::json configJson = nlohmann::json::parse(configStr);
    ipAddress = configJson["ipAddress"];
    freeResource(configBin);
    return ipAddress;
}

BinaryChunk ResourceFileManager::loadResource(std::string& resourceName) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "rb");

    if (f == nullptr) {
        return BinaryChunk { nullptr, 0 };
    }
    
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

nlohmann::json ResourceFileManager::loadResourceJson(std::string &resourceName) {
    BinaryChunk jsonBin = loadResource(resourceName);
    if (jsonBin.data == nullptr) {
        return nlohmann::json();
    }    
    std::string jsonStr((char const*) jsonBin.data, jsonBin.size);
    nlohmann::json json = nlohmann::json::parse(jsonStr);
    Mem::mfree(jsonBin.data);
    return json;
}

InputStream *ResourceFileManager::loadResourceStream(std::string& resourceName) {
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

size_t FileInputStream::read(BinaryChunk chunk) {
    if (!_open) {
        BSOD::raise("read attempt from closed file");
    }
    size_t bufferPos = 0;
    size_t attemptReadSize = 16384;
    while (bufferPos < chunk.size) {
        if (bufferPos + attemptReadSize >= chunk.size) {
            attemptReadSize = chunk.size - bufferPos;
        }
        size_t bytesRead = fread(chunk.data + bufferPos, 1, attemptReadSize, _file);
        bufferPos += bytesRead;
    
        if (bytesRead <= 0) {
            close();
            break;
        }
    }

    _streamPos += bufferPos;
    return bufferPos;
}

size_t FileInputStream::getMaxSize() {
    return _maxSize;
}

void FileInputStream::close() {
    if (_open) {
        fclose(_file);
    }
}
