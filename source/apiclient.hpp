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

enum ApiCommand {
    HEY_DUKE,
    GET_SERVER_ADDR,
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
    std::vector<std::string> request(ApiCommand command);
    std::vector<std::string> request(ApiCommand command, std::vector<std::string>& payload);
private:
    void _init();
    s32 _connect();
    void _disconnect(s32 socket);
    void _sendRequest(s32 socket, ApiCommand command, std::vector<std::string>& payload);
    std::vector<std::string> _recvResponse(s32 socket);
    std::vector<std::string> _responseToLines(std::string& response);
    void _recvBuffered(s32 socket, std::string& response);
    bool _isResponseEnd(std::string& response);
};

#endif // APICLIENT_HPP
