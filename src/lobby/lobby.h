//
// Created by angus.goucher on 4/26/2024.
//

#ifndef NETGAME_LOBBY_H
#define NETGAME_LOBBY_H

#include "../actor.h"
#include "../rectangle.h"

#include <vector>

namespace net {
class Button;
class NameEntry;

class Lobby : public Actor {
public:
    Lobby(net::Button* joinButton, net::Button* beginButton, net::NameEntry* entry, net::State* gameState);

    void Initialize(net::State* state) override;
    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    net::Button* m_JoinButton;
    net::Button* m_BeginButton;
    net::NameEntry* m_NameEntry;
    net::State* m_GameState;

    bool m_Joined = false;
    std::vector<std::string> m_JoinedPlayerNames;
};
}

#endif // NETGAME_LOBBY_H
