//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_NETWORKER_H
#define NETGAME_NETWORKER_H

#include "../actor.h"
#include "../simplesock/socklib.h"

#define NET_NONE_EVENT 0
#define NET_JOIN_LOBBY_EVENT 1
#define NET_REQUEST_LOBBY_NAMES 2

namespace net {
struct ServerEvent {
    unsigned char EventType;
    char Data[255] = { 0 };
};

class Networker {
public:
    Networker();
    Networker(net::Networker& other) = delete;
    void operator=(const net::Networker&) = delete;

    void PostGameEvents(net::EventQueue* queue);
    void SendServerEvent(net::ServerEvent event);

private:
    Socket* m_Socket;
};
};

#endif // NETGAME_NETWORKER_H
