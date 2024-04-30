#include "finish.h"

#include "../game.h"

net::Finish::Finish(net::State* lobbyState, net::Button* returnButton)
    : m_State(lobbyState)
    , m_Button(returnButton)
{

}
void net::Finish::Initialize(net::State* state)
{
}

bool net::Finish::HandleEvent(net::Event event)
{
    return false;
}

void net::Finish::Update(float deltaSeconds)
{
    if (m_Button->WasPressed()) {
        GetGame()->ChangeState(m_State);
    }
}

void net::Finish::Draw(net::Renderer* renderer)
{
}

void net::Finish::DrawUI(net::Renderer* renderer)
{
}