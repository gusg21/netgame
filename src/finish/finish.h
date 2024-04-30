#pragma once

#include "../actor.h"
#include "../lobby/button.h"

namespace net {
class Finish : public Actor {
public:
    Finish(net::State* lobbyState, net::Button* returnButton);

    void Initialize(net::State* state) override;
    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    net::State* m_State;
    net::Button* m_Button;
};
}