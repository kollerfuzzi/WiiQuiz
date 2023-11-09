#include "resourcefilemanager.hpp"

ResourceFileManager::ResourceFileManager() {

}


void ResourceFileManager::init() {
    if (!fatInitDefault()) {
        throw -1;
    }

    const char* dir = "SD:/wiiquiz";
    struct stat sb;
    if (stat(dir, &sb) != 0) {
        mkdir("SD:/wiiquiz", 0777);
    }
}

void ResourceFileManager::saveResource(std::string& resourceName, std::string& contentBase64) {
    std::vector<unsigned char> bytes = base64_decode(contentBase64);

    std::string filePath("SD:/wiiquiz/");
    filePath += resourceName;
    filePath += ".BIN";

    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    file.open(filePath.c_str());
    file.write((char*) bytes.data(), bytes.size());
    file.close();
}

unsigned char* ResourceFileManager::loadResource(std::string &resourceName) {
    std::string filePath("SD:/wiiquiz/");
    filePath += resourceName;
    filePath += ".BIN";

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw -1;
    }
    unsigned char* bytes = new unsigned char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), bytes);
    return bytes;
}

void ResourceFileManager::freeResource(unsigned char* resource) {
    free(resource);
}
