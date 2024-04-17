#include "mjpegio.hpp"
#include "base64.hpp"
#include "json.hpp"
#include "bsod.hpp"

unsigned char START_FRAME[] = {0xff, 0xd8, 0x4a, 0x46, 0x49, 0x46};
unsigned char END_FRAME[] = {0xff, 0xd9};

MjpegIO::MjpegIO(ResourceFileManager* resourceFileManager) {
    _resourceFileManager = resourceFileManager;
}

void MjpegIO::saveMjpeg(std::string& resourceName, BinaryResource b64Data) {
    size_t size;
    unsigned char* buffer = Base64::base64_decode(b64Data.data, b64Data.size, &size);
    if (buffer == nullptr) {
        BSOD::raise("mem allocation failed");
    }

    int startImg = 0;
    int endImg = -1;
    int startSeqPos = 0;
    std::vector<int> soi_eoi; 
    for (size_t pos = 0; pos < size; pos++) {
        if (buffer[pos] == START_FRAME[startSeqPos]) {
            startSeqPos++;
        } else {
            startSeqPos = 0;
        }
        if (startSeqPos == 2) {
            pos += 4;
        }
        if (startSeqPos == 5) {
            startImg = pos - 8;
            startSeqPos = 0;
            if (endImg != -1) {
                endImg = pos - 17;
                soi_eoi.push_back(endImg);
            } else {
                endImg = 0;
            }
            soi_eoi.push_back(startImg); 
        }
        BSOD::raise("dukers");
    }
    BSOD::raise("duker");
    if (soi_eoi.size() % 2 != 0) {
        soi_eoi.pop_back();
    }
    nlohmann::json frames = nlohmann::json::array();
    for (size_t pos = 0; pos < soi_eoi.size() - 2; pos += 2) {
        nlohmann::json frame = {
            {"S", soi_eoi[pos]},
            {"E", soi_eoi[pos + 1]}
        };
        frames.push_back(frame);
    }

    BinaryResource decoded = {
        buffer,
        size
    };
    _resourceFileManager->saveResourcePlain(resourceName, decoded);
    
    std::string frameMetaStr = frames.dump();
    BinaryResource frameMetaStrResource = {
        (unsigned char*) frameMetaStr.c_str(),
        frameMetaStr.size()
    };
    std::string metaName = _getMetaName(resourceName);
    _resourceFileManager->saveResourcePlain(metaName, frameMetaStrResource);
}

Mjpeg MjpegIO::loadMjpeg(std::string& resourceName) {
    BinaryResource mjpegData = _resourceFileManager->loadResource(resourceName);
    // TODO FREE

    std::string metaName = _getMetaName(resourceName);
    BinaryResource meta = _resourceFileManager->loadResource(metaName);
    nlohmann::json metaJson = nlohmann::json::parse(meta.data);
    _resourceFileManager->freeResource(meta);

    unsigned char* data = mjpegData.data;
    
    Mjpeg mjpeg;
    mjpeg.videoData = data;

    for (nlohmann::json metaFrame : metaJson) {
        size_t startOffset = metaFrame["S"];
        size_t endOffset = metaFrame["E"];
        size_t len = endOffset - startOffset;
        Frame frame = {data + startOffset, len};
        mjpeg.frames.push_back(frame);
    }
    return mjpeg;
}

void MjpegIO::freeMjpeg(const Mjpeg& mjpeg) {
    free(mjpeg.videoData);
}

std::string MjpegIO::_getMetaName(std::string &resourceName) {
    std::string metaName = resourceName;
    metaName += "META";
    return metaName;
}
