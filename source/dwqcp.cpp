#include "dwqcp.hpp"
#include "bsod.hpp"



std::string DWQCP::discover() {
    ScreenDebug::printAndRender("DWQCP DISCOVER");
    return DWQCP::waitForOffer();
}


std::string DWQCP::waitForOffer() {
    s32 socket;
    struct sockaddr_in server;

    if ((socket = net_socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        BSOD::raise("DWQCP socket error", socket);
    }

    server.sin_family = PF_INET;
    server.sin_port = 3111;
    server.sin_addr.s_addr = INADDR_ANY;

    if (net_bind(socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        BSOD::raise("DWQCP BIND ERROR");
        exit(2);
    }

    DWQCP::sendDiscover(socket);

    struct sockaddr_in client;
    u32 clientSize = sizeof(client);
    char buffer[32];
    memset(&buffer, 0, 32);

    net_recvfrom(socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &client,
                 &clientSize);

    std::string offer(buffer);
    if (offer != "DWQCPOFFER") {
        BSOD::raise("DWQCP INVALID OFFER");
    }

    printf("Received message %s from domain %s port %d internet\
               address %s\n",
               buffer,
           (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
           ntohs(client.sin_port),
           inet_ntoa(client.sin_addr));

    close(socket);

    std::string serverAddr(inet_ntoa(client.sin_addr));
    return serverAddr;
}

void DWQCP::sendDiscover(s32 socket) {
    std::string discover("DWQCPDISCOVER");

    struct sockaddr_in server;
    u32 serverSize = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_port = 3112;
    server.sin_addr.s_addr = INADDR_BROADCAST;

    if (net_sendto(socket, discover.c_str(), discover.length(), 0,
                   (struct sockaddr *)&server, serverSize) < 0) {
        BSOD::raise("DWQCPOFFER discover error");
    }

    // s32 net_sendto(s32 s,const void *data,s32 len,u32 flags,struct sockaddr *to,socklen_t tolen);
}
