#include "apiclient.hpp"

#include "screendebug.hpp"
#include "stringutils.hpp"
#include "bsod.hpp"
#include "mem.hpp"

#define TCP_PORT 311

APIClient::APIClient() {
    _init();
}

APIClient::~APIClient() {

}

void APIClient::_init() {
    std::string initPrompt = "Initializing Network\n";
    initPrompt += "Connecting to ";
    initPrompt += ipAddress;
    ScreenDebug::printAndRender(initPrompt);
    while(net_init() == -EAGAIN);
}

nlohmann::json APIClient::requestJson(APICommand command) {
    std::string response = request(command);
    nlohmann::json responseJson = nlohmann::json::parse(response);
    _assertStatusOk(responseJson);
    return responseJson;
}

std::string APIClient::request(APICommand command) {
    std::string emptyPayload;
    return request(command, emptyPayload);
}

nlohmann::json APIClient::requestJson(APICommand command, nlohmann::json& payloadJson) {
    std::string payload = payloadJson.dump();
    std::string response = request(command, payload);
    nlohmann::json responseJson = nlohmann::json::parse(response);
    _assertStatusOk(responseJson);
    return responseJson;
}

std::string APIClient::request(APICommand command, std::string& payload) {
    s32 socket = _connect();

    _sendRequest(socket, command, payload);
    std::string response =
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
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    s32 connection_status = net_connect(socket, (struct sockaddr *)&address, sizeof(address));
    if (connection_status < 0) {
        BSOD::raise("Socket connect failed", socket);
    }
    return socket;
}

void APIClient::_disconnect(s32 socket){
    net_close(socket);
}

void APIClient::_assertStatusOk(nlohmann::json json) {
    if (json.contains("status") && json["status"] != "OK") {
        std::string error("ASK_QUESTION returned ");
        error += json["status"];
        BSOD::raise(error);
    }
}

void APIClient::_sendRequest(s32 socket, APICommand command, std::string& payload) {
    auto commandStrView = magic_enum::enum_name(command);
    std::string requestStr(commandStrView);
    requestStr += "\n";
    requestStr += "LEN:";
    requestStr += std::to_string(strlen(payload.c_str()));
    requestStr += "\n";
    requestStr += payload;
    s32 status = net_send(socket, requestStr.c_str(), requestStr.size(), 0);
    if (status < 0) {
        BSOD::raise("Socket send failed", status);
    }
}

std::string APIClient::_recvResponse(s32 socket) {
    std::string response;
    InputStream* istream = _getResponseStream(socket);
    BinaryChunk buffer = BinaryChunk((unsigned char*) Mem::alloc(4096), 4096); 
    while (!istream->isEOF()) {
        size_t dataSize = istream->read(buffer);
        response.append((const char*) buffer.data, dataSize);
    }
    Mem::mfree(buffer.data);
    return response;
}

InputStream* APIClient::_getResponseStream(s32 socket) {
    std::string contentLen;
    char bufferChar = 0;
    do {
        s32 msgLen = net_recv(socket, &bufferChar, 1, 0);
        if (msgLen < 0) {
            BSOD::raise("Socket recv failed (content length)", msgLen);
        }
        contentLen += bufferChar;
    } while (bufferChar != '\n');
    std::vector<std::string> contentLenVector = StringUtils::split(contentLen, ':');
    s32 contentLenInt = std::stoi(contentLenVector[1]);

    return new ApiInputStream(socket, contentLenInt);
}

ApiInputStream::ApiInputStream(s32 socket, size_t contentLen) {
    _socket = socket;
    _contentLen = contentLen;
    _maxSize = contentLen;
}

ApiInputStream::~ApiInputStream() {
    close();
}

size_t ApiInputStream::read(BinaryChunk chunk) {
    if (!_open) {
        BSOD::raise("read attempt from closed socket");
    }
    size_t readLen = chunk.size;
    size_t remainingLen = _contentLen - _streamPos;
    bool closeAfterRecv = false;
    if (readLen >= remainingLen) {
        readLen = remainingLen;
        closeAfterRecv = true;
    }
    unsigned char* content = chunk.data;
    size_t contentPos = 0;
    size_t maxReadLen = 16384;
    while (contentPos < readLen) {
        if (contentPos + maxReadLen > readLen) {
            maxReadLen = readLen - contentPos;
        }
        s32 msgLen = net_recv(_socket, content + contentPos, maxReadLen, 0);
        if (msgLen < 0) {
            BSOD::raise("Socket recv failed (content)", msgLen);
        }
        contentPos += msgLen;
        _streamPos += msgLen;
    }
    
    if (closeAfterRecv) {
        close();
    }

    return readLen;
}

void ApiInputStream::close() {
    if (_open) {
        net_close(_socket);
        _open = false;
    }
}
