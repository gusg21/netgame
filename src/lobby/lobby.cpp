#include "lobby.h"

#include "../game.h"
#include "../state.h"
#include "button.h"
#include "nameentry.h"

net::Lobby::Lobby(net::Button* joinButton, net::Button* beginButton, net::NameEntry* entry, net::State* gameState)
    : m_JoinButton(joinButton)
    , m_BeginButton(beginButton)
    , m_NameEntry(entry)
    , m_GameState(gameState)
{
}

void net::Lobby::Initialize(net::State* state)
{
    m_JoinButton->Revive();
    m_BeginButton->Kill();

    m_Joined = false;
    m_JoinedPlayerNames.clear();

    net::Actor::Initialize(state);
}

bool net::Lobby::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_ACK_JOIN_EVENT) {
        m_Joined = true;
        m_JoinButton->Kill();
    }
    if (event.Type == EVENT_LIST_LOBBY_NAMES_EVENT) {
        m_JoinedPlayerNames.clear();

        std::string names = std::string(event.Data.AsListLobbyNamesEvent.names);
        size_t pos = 0;
        std::string token;
        while ((pos = names.find(';')) != std::string::npos) {
            token = names.substr(0, pos);
            m_JoinedPlayerNames.push_back(token);
            names.erase(0, pos + 1);
        }
        m_JoinedPlayerNames.push_back(names);
    }
    if (event.Type == EVENT_START_GAME_EVENT) {
        if (m_Joined) {
            GetGame()->ChangeState(m_GameState);
        }
    }
    return false;
}

void net::Lobby::Update(float deltaSeconds)
{
    if (m_JoinButton->WasPressed() && *m_NameEntry->GetName() != '\0') {
        ServerEvent event = {
            .EventType = NET_SERVER_JOIN_LOBBY
        };
        memcpy(event.Data, m_NameEntry->GetName(), 254);
        GetGame()->GetNetworker()->SendServerEvent(event);
    }

    if (m_BeginButton->WasPressed()) {
        GetGame()->GetNetworker()->SendServerEvent({ .EventType = NET_SERVER_REQUEST_START_GAME });
    }

    if (GetState()->GetFrameNumber() % 1000 == 0) {
        GetGame()->GetNetworker()->SendServerEvent({ .EventType = NET_SERVER_REQUEST_LOBBY_NAMES });
    }

    if (m_JoinedPlayerNames.size() > 1 && !m_BeginButton->IsAlive()) {
        m_BeginButton->Revive();
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

    for (uint32_t i = 0; i < m_JoinedPlayerNames.size(); i++) {
        renderer->DrawText(m_JoinedPlayerNames[i].c_str(), 10, 10, 100 + (15 * i), C8BLUE);
    }
}
