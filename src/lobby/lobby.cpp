#include "lobby.h"

#include "button.h"
#include "../state.h"
#include "../game.h"
#include "nameentry.h"

net::Lobby::Lobby(net::Button* joinButton, net::NameEntry* entry)
    : m_JoinButton(joinButton)
    , m_NameEntry(entry)
{
}

bool net::Lobby::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_ACK_JOIN_EVENT) {
        m_Joined = true;
        m_JoinButton->Kill();
    }
    if (event.Type == EVENT_LIST_LOBBY_NAMES_EVENT) {
        m_LobbyNames.clear();

        std::string names = std::string(event.Data.AsListLobbyNamesEvent.names);
        size_t pos = 0;
        std::string token;
        while ((pos = names.find(';')) != std::string::npos) {
            token = names.substr(0, pos);
            m_LobbyNames.push_back(token);
            names.erase(0, pos + 1);
        }
        m_LobbyNames.push_back(names);
    }
    return false;
}

void net::Lobby::Update(float deltaSeconds)
{
    if (m_JoinButton->WasPressed()) {
        ServerEvent event = {
            .EventType = NET_JOIN_LOBBY_EVENT
        };
        memcpy(event.Data, m_NameEntry->GetName(), 254);
        GetGame()->GetNetworker()->SendServerEvent(event);
    }

    if (GetState()->GetFrameNumber() % 1000 == 0) {
        GetGame()->GetNetworker()->SendServerEvent({
            .EventType = NET_REQUEST_LOBBY_NAMES
            });
    }
}

void net::Lobby::Draw(net::Renderer* renderer)
{
}

void net::Lobby::DrawUI(net::Renderer* renderer)
{
    if (m_Joined) {
        renderer->DrawText("Joined!", 20, 10, 70, C8WHITE);
    }

    for (uint32_t i = 0; i < m_LobbyNames.size(); i++) {
        renderer->DrawText(m_LobbyNames[i].c_str(), 10, 10, 100 + (15 * i), C8BLUE);
    }
}
