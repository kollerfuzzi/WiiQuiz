#include "resourceapiclient.hpp"
#include "json.hpp"

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

std::string ResourceAPIClient::fetchResource(std::string resourcePath) {
    std::vector<std::string> payload;
    payload.push_back(resourcePath);
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCE, payload);
    return response[0];
}
