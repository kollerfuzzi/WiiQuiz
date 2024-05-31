#ifndef APICLIENT_HPP
#define APICLIENT_HPP

#include <cstdint>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <network.h>
#include <errno.h>
#include <sys/dir.h>
#include <vector>
#include "magic_enum.hpp"
#include "json.hpp"
#include "io_stream.hpp"

enum APICommand {
    REGISTER_WII,
    UNREGISTER_WII,
    GET_SERVERADDR,
    GET_QUIZZES,
    GET_FILE,
    GET_FILEHASH,
    GET_RESOURCESVERSION,
    GET_PLAYERS,
    ASK_QUESTION,
    END_QUESTION,
    GET_ANSWERS,
    SET_POINTS
};

class ApiInputStream : public InputStream {
public:
    ApiInputStream(s32 socket, size_t contentLen);
    ~ApiInputStream();
    size_t read(BinaryChunk chunk);
    void close();
private:
    s32 _socket = 0;
    size_t _contentLen = 0;
};


class APIClient {
public:
    APIClient();
    ~APIClient();
    nlohmann::json requestJson(APICommand command);
    std::string request(APICommand command);
    nlohmann::json requestJson(APICommand, nlohmann::json& json);
    std::string request(APICommand command, std::string& payload);
    static std::string ipAddress;
protected:
    void _init();
    s32 _connect();
    void _disconnect(s32 socket);
    void _assertStatusOk(nlohmann::json status);
    void _sendRequest(s32 socket, APICommand command, std::string& payload);
    std::string _recvResponse(s32 socket);
    InputStream* _getResponseStream(s32 socket);
    char* _recvBuffered(s32 socket, u16 bufferSize);
    void _clearBuffer(char* buffer);
    u16 _bufferSize(std::string string);
    bool _isResponseEnd(std::string response);
};

#endif // APICLIENT_HPP
