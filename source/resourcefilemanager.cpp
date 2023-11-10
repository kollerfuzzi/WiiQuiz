#include "resourcefilemanager.hpp"

ResourceFileManager::ResourceFileManager() {
    init();
}


void ResourceFileManager::init() {
    if (!fatInitDefault()) {
        throw -1;
    }
}

void ResourceFileManager::saveTestFile() {
    std::string fileName("ZWQ_TEST.BIN");
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == NULL) {
        throw -1;
    } else {
        std::string content("hey");
        fwrite(&content[0], 1, content.size(), f);
        fclose(f);
    }
}

void ResourceFileManager::saveResource(std::string& resourceName, std::string& contentBase64) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == NULL) {
        throw -1;
    } else {
        std::string base = base64_decode(contentBase64);
        fwrite(&base[0], 1, base.size(), f);
        fclose(f);
    }
}

void ResourceFileManager::saveResourcePlain(std::string &resourceName, std::string& contentPlain){
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "wb");
    if (f == NULL) {
        throw -1;
    } else {
        fwrite(&contentPlain[0], 1, contentPlain.size(), f);
        fclose(f);
    }
}

BinaryResource ResourceFileManager::loadResource(std::string& resourceName) {
    std::string fileName = _resourceNameToFileName(resourceName);
    FILE* f = fopen(fileName.c_str(), "rb");

    if (f == NULL) {
        return BinaryResource { nullptr, 0 };
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

        unsigned char* bytes = (unsigned char*)malloc(content.size());
        std::copy(content.begin(), content.end(), bytes);
        fclose(f);
        return BinaryResource(bytes, content.size());
    }
}

void ResourceFileManager::freeResource(const BinaryResource& resource) {
    free(resource.data);
}

std::string ResourceFileManager::_resourceNameToFileName(std::string &resourceName) {
    std::string fileName("ZWQ_");
    fileName += resourceName;
    fileName += ".BIN";
    return fileName;

}
