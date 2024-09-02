#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"
#include "io_stream.hpp"
#include <set>

class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    ~ResourceAPIClient();
    std::string fetchResourceHash(std::string& resourcePath);
    void cacheResourceHashes(std::set<std::string>& resourcePaths);
    void clearCache();
    s32 fetchResourceVersion();
    void registerWii();
    void unregisterWii();
    InputStream* fetchResource(std::string& resourcePath);
private:
    std::map<std::string, std::string> _cachedResourceHashes;
};

#endif // RESOURCEAPICLIENT_HPP
