#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdint>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <network.h>
#include <errno.h>
#include <sys/dir.h>
#include "magic_enum.hpp"

enum ApiCommand {
    HEY_DUKE,
    GET_PLAYERS,
    ASK_QUESTION,
    END_QUESTION,
    GET_ANSWERS
};

class WiiAPIClient
{
public:
    WiiAPIClient();
    void init();
    std::string request(ApiCommand command);
    std::string request(ApiCommand command, std::string payload);
private:
    s32 _connect();
    void _disconnect(s32 socket);
    void _sendRequest(s32 socket, ApiCommand command, std::string payload);
    std::string _recvResponse(s32 socket);
    void _recvBuffered(s32 socket, std::string& response);
    bool _isResponseEnd(std::string& response);
};

#endif // SERVER_HPP
