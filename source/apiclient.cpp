#include "apiclient.hpp"

#include "screendebug.hpp"
#include "stringutils.hpp"

#define TCP_PORT 311

APIClient::APIClient() {
    _init();
}

void APIClient::_init() {
    while(net_init() == -EAGAIN);
}

std::vector<std::string> APIClient::request(ApiCommand command) {
    std::vector<std::string> emptyPayload;
    return request(command, emptyPayload);
}

std::vector<std::string> APIClient::request(ApiCommand command, std::vector<std::string>& payload) {
    s32 socket = _connect();

    _sendRequest(socket, command, payload);
    std::vector<std::string> response =
       _recvResponse(socket);

    _disconnect(socket);
    return response;
}

s32 APIClient::_connect() {
    struct sockaddr_in address;
    s32 socket = net_socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
    address.sin_family = AF_INET;
    address.sin_port = htons(3110);
    address.sin_addr.s_addr = inet_addr("10.0.0.2");
    net_connect(socket, (struct sockaddr *)&address, sizeof(address));
    return socket;
}

void APIClient::_disconnect(s32 socket){
    net_close(socket);
}

void APIClient::_sendRequest(s32 socket, ApiCommand command, std::vector<std::string>& payload) {
    auto commandStrView = magic_enum::enum_name(command);
    std::string commandStr(commandStrView);
    commandStr += "\n";
    for (std::string& line : payload) {
        commandStr += line;
        commandStr += "\n";
    }
    commandStr += "\n";
    net_send(socket, commandStr.c_str(), commandStr.size(), 0);
}

std::vector<std::string> APIClient::_recvResponse(s32 socket) {
    std::string response;
    do {
        _recvBuffered(socket, response);
    } while (!_isResponseEnd(response));
    return _responseToLines(response);
}

std::vector<std::string> APIClient::_responseToLines(std::string &response) {
    std::vector<std::string> lines = StringUtils::split(response, '\n');
    std::vector<std::string> nonEmptyLines;
    for (std::string& line : lines) {
        if (line.size() != 0) {
            nonEmptyLines.push_back(line);
        }
    }
    return nonEmptyLines;
}

void APIClient::_recvBuffered(s32 socket, std::string &response) {
    char buffer[1024];
    s32 msgLen = net_recv(socket, buffer, 1024, 0);
    if (msgLen <= 0) {
        response += "\n";
        return;
    }
    std::string responseBuffer;
    responseBuffer += buffer;
    response += responseBuffer.substr(0, msgLen);
}

bool APIClient::_isResponseEnd(std::string &response) {
    return response.size() >= 2
        && response.substr(response.size() - 2, 2) == MSG_END;
}



