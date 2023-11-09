#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"
class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    std::string fetchResourceVersion();
    std::string fetchResource(std::string resourcePath);
};

#endif // RESOURCEAPICLIENT_HPP
