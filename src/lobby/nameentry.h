//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_NAMEENTRY_H
#define NETGAME_NAMEENTRY_H

#include "../actor.h"

namespace net {
class NameEntry : public Actor {
public:
    NameEntry();

    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    char m_NameBuffer[256];
    unsigned char m_NameBufferCursor = 0;
};
}

#endif