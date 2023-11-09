#include "resourceapiclient.hpp"

ResourceAPIClient::ResourceAPIClient() {

}

std::string ResourceAPIClient::fetchResourceVersion() {
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCES_VERSION);
    return response[0];
}

std::string ResourceAPIClient::fetchResource(std::string resourcePath) {
    std::vector<std::string> payloard;
    payloard.push_back(resourcePath);
    std::vector<std::string> response =
        request(APICommand::GET_RESOURCE, payloard);
    return response[0];
}
