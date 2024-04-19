#include "resourceapiclient.hpp"
#include "json.hpp"
#include "bsod.hpp"
#include "stringutils.hpp"
#include "mem.hpp"

ResourceAPIClient::ResourceAPIClient() {

}

ResourceAPIClient::~ResourceAPIClient() {

}

s32 ResourceAPIClient::fetchResourceVersion() {
    nlohmann::json response =
        requestJson(APICommand::GET_RESOURCES_VERSION);
    s32 resourceVersionNumber = response["resourceVersion"];
    return resourceVersionNumber;
}

void ResourceAPIClient::registerWii() {
    requestJson(APICommand::REGISTER_WII);
}

void ResourceAPIClient::unregisterWii() {
    requestJson(APICommand::UNREGISTER_WII);
}

ApiInputStream* ResourceAPIClient::fetchResource(std::string resourcePath) {
    std::vector<std::string> payload;
    payload.push_back(resourcePath);

    s32 socket = _connect();

    _sendRequest(socket, APICommand::GET_RESOURCE, payload);
    std::string contentLen;
    char bufferChar = 0;
    do {
        s32 msgLen = net_recv(socket, &bufferChar, 1, 0);
        if (msgLen < 0) {
            BSOD::raise("Socket recv failed (content length)", msgLen);
        }
        contentLen += bufferChar;
    } while (bufferChar != '\n');
    std::vector<std::string> contentLenVector = StringUtils::split(contentLen, ':');
    s32 contentLenInt = std::stoi(contentLenVector[1]);

    return new ApiInputStream(socket, contentLenInt);
}

ApiInputStream::ApiInputStream(s32 socket, size_t contentLen) {
    _socket = socket;
    _contentLen = contentLen;
    _maxSize = contentLen;
}

ApiInputStream::~ApiInputStream() {
    close();
}

BinaryChunk ApiInputStream::read(size_t maxLen) {
    if (!_open) {
        BSOD::raise("read attempt from closed socket");
    }
    size_t readLen = maxLen;
    size_t remainingLen = _contentLen - _streamPos;
    bool closeAfterRecv = false;
    if (readLen >= remainingLen) {
        readLen = remainingLen;
        closeAfterRecv = true;
    }
    unsigned char* content = (unsigned char*) Mem::alloc(readLen);
    size_t contentPos = 0;
    size_t maxReadLen = 16384;
    std::string log("read len ");
    log += std::to_string(readLen);
    log += " remaining len ";
    log += std::to_string(remainingLen);
    log += " closeAfterRecv ";
    log += std::to_string(closeAfterRecv);
    log += " contentPos ";
    log += std::to_string(contentPos);
    log += " maxReadLen ";
    log += std::to_string(maxReadLen);
    //BSOD::raise(log);
    while (contentPos < readLen) {
        if (contentPos + maxReadLen > readLen) {
            // 50 + 20 > 60
            // cp + mr > rl
            // 50 + 10 = 60
            maxReadLen = readLen - contentPos;
        }
        s32 msgLen = net_recv(_socket, content + contentPos, maxReadLen, 0);
        if (msgLen < 0) {
            BSOD::raise("Socket recv failed (content)", msgLen);
        }
        contentPos += msgLen;
        _streamPos += msgLen;
    }
    
    if (closeAfterRecv) {
        close();
    }

    BinaryChunk resource(content, readLen);
    return resource;
}

void ApiInputStream::close() {
    if (_open) {
        net_close(_socket);
        _open = false;
    }
}
