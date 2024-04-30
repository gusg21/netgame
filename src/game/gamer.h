//
// Created by angus.goucher on 4/26/2024.
//

#ifndef NETGAME_GAMER_H
#define NETGAME_GAMER_H

#include "../actor.h"
#include "../rectangle.h"

#include <vector>
#include "card.h"

namespace net {

class Gamer : public Actor {
public:
    Gamer(net::State* state);

    void Initialize(net::State* state) override;
    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    std::array<net::Card, EVENT_MAX_NUM_CARD_STATES> m_Cards;
    net::State* m_State;
};
}

#endif // NETGAME_GAMER_H
