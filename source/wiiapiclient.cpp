#include "wiiapiclient.hpp"

#include "screendebug.hpp"

#define TCP_PORT 311

WiiAPIClient::WiiAPIClient() {

}

void WiiAPIClient::init() {
    while(net_init() == -EAGAIN);
}

std::string WiiAPIClient::request(ApiCommand command) {
    s32 socket = _connect();

    _sendRequest(socket, command, std::string());
    std::string response =
        _recvResponse(socket);

    ScreenDebug::printLn(response);

    _disconnect(socket);
    return response;
}

std::string WiiAPIClient::request(ApiCommand command, std::string payload) {
    return std::string("not implemented");
}

s32 WiiAPIClient::_connect() {
    struct sockaddr_in address;
    s32 socket = net_socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
    address.sin_family = AF_INET;
    address.sin_port = htons (3110);
    address.sin_addr.s_addr = inet_addr("10.0.0.2");
    net_connect(socket, (struct sockaddr *)&address, sizeof(address));
    return socket;
}

void WiiAPIClient::_disconnect(s32 socket){
    close(socket);
}

void WiiAPIClient::_sendRequest(s32 socket, ApiCommand command, std::string payload) {
    auto commandStrView = magic_enum::enum_name(command);
    std::string commandStr(commandStrView);
    commandStr += "\n\n";
    net_send(socket, commandStr.c_str(), commandStr.size(), 0);
}

std::string WiiAPIClient::_recvResponse(s32 socket) {
    std::string response;
    do {
        _recvBuffered(socket, response);
    } while (!_isResponseEnd(response));
    return response;
}

void WiiAPIClient::_recvBuffered(s32 socket, std::string &response) {
    char buffer[128];
    s32 msgLen = net_recv(socket, buffer, 128, 0);
    if (msgLen < 0) {
        throw -1; // todo exception handling
    }
    std::string responseBuffer;
    responseBuffer += buffer;
    response+= responseBuffer.substr(0, msgLen);
}

bool WiiAPIClient::_isResponseEnd(std::string &response) {
    return response.size() >= 2
        && response.substr(response.size() - 2, 2) == "\n\n";
}



