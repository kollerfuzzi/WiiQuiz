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
    if (_cachedResourceHashes.contains(resourcePath)) {
        return _cachedResourceHashes[resourcePath];
    }
    nlohmann::json request = {
        {"filePaths", {resourcePath}}
    };
    nlohmann::json response = requestJson(APICommand::GET_FILEHASHES, request);
    return response["fileHashes"][resourcePath];
}

void ResourceAPIClient::cacheResourceHashes(std::set<std::string> &resourcePaths) {
    nlohmann::json request;
    request["filePaths"] = resourcePaths;
    nlohmann::json response = requestJson(APICommand::GET_FILEHASHES, request);
    std::map<std::string, std::string> fileHashes = response["fileHashes"];
    for (auto& [key, value] : fileHashes) {
        _cachedResourceHashes[key] = value;
    }
}

s32 ResourceAPIClient::fetchResourceVersion() {
    nlohmann::json response =
        requestJson(APICommand::GET_RESOURCESVERSION);
    s32 resourceVersionNumber = response["resourceVersion"];
    return resourceVersionNumber;
}

void ResourceAPIClient::clearCache() {
    _cachedResourceHashes.clear();
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