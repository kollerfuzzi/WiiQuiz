#include "resourceapiclient.hpp"
#include "json.hpp"
#include "bsod.hpp"
#include "stringutils.hpp"

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

std::string ResourceAPIClient::fetchResourceOld(std::string resourcePath) {
    std::vector<std::string> payload;
    payload.push_back(resourcePath);
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCE, payload);
    return response[0];
}

BinaryResource ResourceAPIClient::fetchResource(std::string resourcePath) {
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
    unsigned char* content = (unsigned char*) malloc(contentLenInt);
    unsigned char* currentPos = content;
    unsigned char* endPos = content + contentLenInt;
    bool lastFrame = false;
    do {
        s32 readLen = endPos - currentPos;
        if (readLen > 32768) {
            readLen = 32768;
        } else {
            lastFrame = true;
        }
        s32 msgLen = net_recv(socket, currentPos, readLen, 0);
        if (msgLen < 0) {
            BSOD::raise("Socket recv failed (content)", msgLen);
        }
        currentPos += readLen;
    } while (!lastFrame);
    //s32 msgLen = net_recv(socket, content, contentLenInt, 0);
    //if (msgLen < 0) {
    //    BSOD::raise("Socket recv failed (content)", msgLen);
    //}

    _disconnect(socket);
    BinaryResource resource = {content, contentLenInt};
    return resource;
}
