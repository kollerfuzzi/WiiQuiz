#include "resourceapiclient.hpp"

ResourceAPIClient::ResourceAPIClient() {

}

ResourceAPIClient::~ResourceAPIClient() {

}

std::string ResourceAPIClient::fetchResourceVersion() {
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCES_VERSION);
    return response[0];
}

std::string ResourceAPIClient::fetchResource(std::string resourcePath) {
    std::vector<std::string> payload;
    payload.push_back(resourcePath);
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCE, payload);
    return response[0];
}
