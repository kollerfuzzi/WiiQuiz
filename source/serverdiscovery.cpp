#include "serverdiscovery.hpp"
#include <network.h>
#include "bsod.hpp"
#include "screendebug.hpp"

std::string ServerDiscovery::waitForServerGetAddr() {
    ScreenDebug::printAndRender("Initializing network...");
    while(net_init() == -EAGAIN);

    struct sockaddr_in cliAddr, servAddr;

    s32 socket = net_socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (socket < 0) {
        BSOD::raise("socket create failed", socket);
    }

    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(3111);

    s32 opt = 1;
    net_setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    s32 status = net_bind(socket, (struct sockaddr *) &servAddr,
              sizeof (servAddr));
    if (status < 0) {
        BSOD::raise("socket bind failed", status);
    }

    char buffer[1025];
    std::string serverAddr;

    ScreenDebug::printAndRender("Discovering server...");
    while (true) {
        memset(buffer, 0, 1025);
        u32 len = sizeof(cliAddr);
        s32 msgLen = net_recvfrom(socket, buffer, 1024, 0,
                    (struct sockaddr *) &cliAddr, &len );
        std::string dataStr = buffer;

        if (msgLen > 0 || dataStr == "WII_SERVER_DISCOVERY") {
            serverAddr = inet_ntoa(cliAddr.sin_addr);
            break;
        }
    }
    net_close(socket);


    ScreenDebug::printAndRender("Server found, connectiong to " + serverAddr);

    return serverAddr;
}