//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_COMBINEPARTS_H
#define NETGAME_COMBINEPARTS_H

#include "../actor.h"

namespace net {
struct Particle {
    float X, Y;
    float VelX, VelY;
    float Gravity;
};

class CombineParts : public Actor {
public:
    CombineParts(float x, float y);

    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;

private:
    std::array<Particle, 128> m_Parts;
};
}

#endif // NETGAME_COMBINEPARTS_H
