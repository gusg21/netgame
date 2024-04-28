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
    Lobby(net::Button* joinButton, net::NameEntry* entry);

    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    net::Button* m_JoinButton;
    net::NameEntry* m_NameEntry;

    bool m_Joined = false;
    std::vector<std::string> m_LobbyNames;
};
}

#endif // NETGAME_LOBBY_H
