//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_NETWORKER_H
#define NETGAME_NETWORKER_H

#include "../actor.h"
#include "../simplesock/socklib.h"

namespace net {
class Networker {
public:
    Networker();
    Networker(Networker& other) = delete;
    void operator=(const Networker&) = delete;

    void PostEvents(EventQueue* queue);

private:
    Socket* m_Socket;
};
};

#endif // NETGAME_NETWORKER_H
