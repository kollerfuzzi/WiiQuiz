#ifndef RESOURCEAPICLIENT_HPP
#define RESOURCEAPICLIENT_HPP

#include "apiclient.hpp"
#include "io_stream.hpp"

class ApiInputStream : public InputStream {
public:
    ApiInputStream(s32 socket, size_t contentLen);
    ~ApiInputStream();
    BinaryChunk read(size_t maxLen);
    void close();
private:
    s32 _socket = 0;
    size_t _contentLen = 0;
};

class ResourceAPIClient : public APIClient {
public:
    ResourceAPIClient();
    ~ResourceAPIClient();
    s32 fetchResourceVersion();
    void registerWii();
    void unregisterWii();
    ApiInputStream* fetchResource(std::string resourcePath);
};

#endif // RESOURCEAPICLIENT_HPP
