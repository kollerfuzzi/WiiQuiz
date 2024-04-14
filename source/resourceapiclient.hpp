#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"

class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    ~ResourceAPIClient();
    s32 fetchResourceVersion();
    void registerWii();
    void unregisterWii();
    std::string fetchResource(std::string resourcePath);
};

#endif // RESOURCEAPICLIENT_HPP
