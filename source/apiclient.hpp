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

enum APICommand {
    REGISTER_WII,
    UNREGISTER_WII,
    GET_SERVER_ADDR,
    GET_RESOURCE,
    GET_RESOURCES_VERSION,
    GET_PLAYERS,
    ASK_QUESTION,
    END_QUESTION,
    GET_ANSWERS,
    SET_POINTS
};

#define MSG_END "\n\n"

class APIClient {
public:
    APIClient();
    ~APIClient();
    nlohmann::json requestJson(APICommand command);
    std::vector<std::string> request(APICommand command);
    nlohmann::json requestJson(APICommand, nlohmann::json json);
    std::vector<std::string> request(APICommand command, std::vector<std::string> payload);
    static std::string ipAddress;
private:
    void _init();
    s32 _connect();
    void _disconnect(s32 socket);
    void _assertStatusOk(nlohmann::json status);
    void _sendRequest(s32 socket, APICommand command, std::vector<std::string> payload);
    std::vector<std::string> _recvResponse(s32 socket);
    std::vector<std::string> _responseToLines(std::string response);
    char* _recvBuffered(s32 socket, u16 bufferSize);
    void _clearBuffer(char* buffer);
    u16 _bufferSize(std::string string);
    bool _isResponseEnd(std::string response);
};

#endif // APICLIENT_HPP
