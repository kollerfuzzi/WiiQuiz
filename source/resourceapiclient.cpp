#include "resourceapiclient.hpp"
#include "json.hpp"
#include "bsod.hpp"
#include "stringutils.hpp"
#include "mem.hpp"

ResourceAPIClient::ResourceAPIClient() {

}

ResourceAPIClient::~ResourceAPIClient() {

}

std::string ResourceAPIClient::fetchResourceHash(std::string &resourcePath) {
    nlohmann::json request = {
        {"filePath", resourcePath}
    };
    nlohmann::json response = requestJson(APICommand::GET_FILEHASH, request);
    return response["hash"];
}

s32 ResourceAPIClient::fetchResourceVersion() {
    nlohmann::json response =
        requestJson(APICommand::GET_RESOURCESVERSION);
    s32 resourceVersionNumber = response["resourceVersion"];
    return resourceVersionNumber;
}

void ResourceAPIClient::registerWii() {
    requestJson(APICommand::REGISTER_WII);
}

void ResourceAPIClient::unregisterWii() {
    requestJson(APICommand::UNREGISTER_WII);
}

InputStream* ResourceAPIClient::fetchResource(std::string& resourcePath) {
    s32 socket = _connect();
    _sendRequest(socket, APICommand::GET_FILE, resourcePath);
    return _getResponseStream(socket);
}