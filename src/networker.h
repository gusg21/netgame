//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_NETWORKER_H
#define NETGAME_NETWORKER_H

#include "../actor.h"
#include "../simplesock/socklib.h"

#define NET_NONE_EVENT                  0

#define NET_SERVER_JOIN_LOBBY           1
#define NET_SERVER_REQUEST_LOBBY_NAMES  2
#define NET_SERVER_REQUEST_START_GAME   3
#define NET_SERVER_REQUEST_CARD_STATE   4
#define NET_SERVER_MOVE_CARD            5
#define NET_SERVER_PUT_DOWN_CARD        6
#define NET_SERVER_PICK_UP_CARD         7

#define NET_CLIENT_QUIT                     1
#define NET_CLIENT_ACK_JOIN                 2
#define NET_CLIENT_LIST_LOBBY_NAMES         3
#define NET_CLIENT_START_GAME               4
#define NET_CLIENT_CARD_STATE               5
#define NET_CLIENT_DONT_WORRY_ABOUT_IT      6
#define NET_CLIENT_ALLOW_CARD_MOVE          7
#define NET_CLIENT_FINISH_CARD_MOVE         8
#define NET_CLIENT_CARDS_COMBINED           9
#define NET_CLIENT_GAME_FINISHED            10

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
