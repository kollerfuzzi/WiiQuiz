#include "mjpegio.hpp"
#include "json.hpp"
#include "bsod.hpp"
#include "mem.hpp"
#include "stddef.h"

unsigned char START_FRAME[] = {0xff, 0xd8, 0x4a, 0x46, 0x49, 0x46};
unsigned char END_FRAME[] = {0xff, 0xd9};

MjpegIO::MjpegIO(ResourceFileManager* resourceFileManager) {
    _resourceFileManager = resourceFileManager;
}

void MjpegIO::saveMjpegStream(std::string& resourceName, InputStream* stream) {
    // todo fix non streaming;
    size_t fileSize = stream->getMaxSize();
    unsigned char* data = (unsigned char*) Mem::alloc(fileSize);
    
    size_t datapos = 0;
    do {
        BinaryChunk resource = stream->read(16384);
        memcpy(data + datapos, resource.data, resource.size);
        datapos += resource.size;
        Mem::mfree(resource.data);
    } while(!stream->isEOF());
    
    int startImg = 0;
    int endImg = -1;
    int startSeqPos = 0;
    std::vector<int> soi_eoi; 
    for (size_t pos = 0; pos < fileSize; pos++) {
        if (data[pos] == START_FRAME[startSeqPos]) {
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
    }
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

    BinaryChunk file(data, fileSize);
    _resourceFileManager->saveResource(resourceName, file);
    Mem::mfree(data);
    
    std::string frameMetaStr = frames.dump();
    BinaryChunk frameMetaStrResource = {
        (unsigned char*) frameMetaStr.c_str(),
        frameMetaStr.size()
    };
    std::string metaName = _getMetaName(resourceName);
    _resourceFileManager->saveResource(metaName, frameMetaStrResource);
}

Mjpeg MjpegIO::loadMjpegMeta(std::string& resourceName) {
    std::string metaName = _getMetaName(resourceName);
    BinaryChunk meta = _resourceFileManager->loadResource(metaName);
    std::string metaString((char const*)(meta.data), meta.size) ;
    nlohmann::json metaJson = nlohmann::json::parse(metaString);
    _resourceFileManager->freeResource(meta);

    std::vector<Frame> frames;

    for (nlohmann::json metaFrame : metaJson) {
        size_t startOffset = metaFrame["S"];
        size_t endOffset = metaFrame["E"];
        Frame frame = {startOffset, endOffset};
        frames.push_back(frame);
    }
    
    return Mjpeg(frames);
}

std::string MjpegIO::_getMetaName(std::string &resourceName) {
    std::string metaName = resourceName;
    metaName += "META";
    return metaName;
}
