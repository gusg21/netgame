//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_NETWORKER_H
#define NETGAME_NETWORKER_H

#include "../actor.h"
#include "../simplesock/socklib.h"

#define NET_NONE_EVENT                  0

#define NET_SERVER_JOIN_LOBBY_EVENT     1
#define NET_SERVER_REQUEST_LOBBY_NAMES  2
#define NET_SERVER_REQUEST_START_GAME   3
#define NET_SERVER_REQUEST_CARD_STATE   4
#define NET_SERVER_MOVE_CARD            5

#define NET_CLIENT_QUIT_EVENT               1
#define NET_CLIENT_ACK_JOIN_EVENT           2
#define NET_CLIENT_LIST_LOBBY_NAMES_EVENT   3
#define NET_CLIENT_START_GAME               4
#define NET_CLIENT_CARD_STATE               5

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
