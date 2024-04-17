#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"
#include "binaryresource.hpp"

class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    ~ResourceAPIClient();
    s32 fetchResourceVersion();
    void registerWii();
    void unregisterWii();
    std::string fetchResourceOld(std::string resourcePath);
    BinaryResource fetchResource(std::string resourcePath);
};

#endif // RESOURCEAPICLIENT_HPP
