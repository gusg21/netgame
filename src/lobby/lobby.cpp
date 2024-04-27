#include "lobby.h"

#include "button.h"

net::Lobby::Lobby(net::Button* joinButton, net::NameEntry* entry)
    : m_JoinButton(joinButton)
    , m_NameEntry(entry)
{
}

bool net::Lobby::HandleEvent(net::Event event)
{
    return false;
}

void net::Lobby::Update(float deltaSeconds)
{
    if (m_JoinButton->WasPressed()) {
        printf("Down!\n");
    }
}

void net::Lobby::Draw(net::Renderer* renderer)
{
}

void net::Lobby::DrawUI(net::Renderer* renderer)
{
}
