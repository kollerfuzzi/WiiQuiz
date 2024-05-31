#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"
#include "io_stream.hpp"

class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    ~ResourceAPIClient();
    std::string fetchResourceHash(std::string& resourcePath);
    s32 fetchResourceVersion();
    void registerWii();
    void unregisterWii();
    InputStream* fetchResource(std::string& resourcePath);
};

#endif // RESOURCEAPICLIENT_HPP
