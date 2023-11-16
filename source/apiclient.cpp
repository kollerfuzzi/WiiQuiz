#include "apiclient.hpp"

#include "screendebug.hpp"
#include "stringutils.hpp"
#include "bsod.hpp"

#define TCP_PORT 311

APIClient::APIClient() {
    _init();
}

APIClient::~APIClient() {

}

void APIClient::_init() {
    ScreenDebug::printLn("Initializing Network...");
    ScreenDebug::render();
    GRRLIB_Render();
    while(net_init() == -EAGAIN);
    ScreenDebug::clear();
}

std::vector<std::string> APIClient::request(APICommand command) {
    std::vector<std::string> emptyPayload;
    return request(command, emptyPayload);
}

std::vector<std::string> APIClient::request(APICommand command, std::vector<std::string> payload) {
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
    if (socket < 0) {
        BSOD::raise("Socket create failed", socket);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(3110);
    address.sin_addr.s_addr = inet_addr(_address.c_str());
    s32 connection_status = net_connect(socket, (struct sockaddr *)&address, sizeof(address));
    if (connection_status < 0) {
        BSOD::raise("Socket connect failed", socket);
    }
    return socket;
}

void APIClient::_disconnect(s32 socket){
    net_close(socket);
}

void APIClient::_sendRequest(s32 socket, APICommand command, std::vector<std::string> payload) {
    auto commandStrView = magic_enum::enum_name(command);
    std::string commandStr(commandStrView);
    commandStr += "\n";
    for (std::string line : payload) {
        commandStr += line;
        commandStr += "\n";
    }
    commandStr += "\n";
    s32 status = net_send(socket, commandStr.c_str(), commandStr.size(), 0);
    if (status != 0) {
        BSOD::raise("Socket send failed", status);
    }
}

std::vector<std::string> APIClient::_recvResponse(s32 socket) {
    std::string response;
    do {
        response += _recvBuffered(socket);
    } while (!_isResponseEnd(response));
    return _responseToLines(response);
}

std::vector<std::string> APIClient::_responseToLines(std::string response) {
    std::vector<std::string> lines = StringUtils::split(response, '\n');
    std::vector<std::string> nonEmptyLines;
    for (std::string line : lines) {
        if (line.size() != 0) {
            nonEmptyLines.push_back(line);
        }
    }
    return nonEmptyLines;
}

std::string APIClient::_recvBuffered(s32 socket) {
    char buffer[1024];
    s32 msgLen = net_recv(socket, buffer, 1024, 0);
    if (msgLen == 0) {
        return std::string("\n");
    } else if (msgLen < 0) {
        BSOD::raise("Socket recv failed", msgLen);
    }
    std::string responseBuffer;
    responseBuffer += buffer;
    return responseBuffer.substr(0, msgLen);
}

bool APIClient::_isResponseEnd(std::string response) {
    return response.size() >= 2
        && response.substr(response.size() - 2, 2) == MSG_END;
}



