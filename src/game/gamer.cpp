#include "gamer.h"

#include "../game.h"
#include "../networker.h"

net::Gamer::Gamer() 
    : m_Cards()
{
}

void net::Gamer::Initialize(net::State* state)
{
    net::Actor::Initialize(state);

    for (uint32_t i = 0; i < EVENT_MAX_NUM_CARD_STATES; i++) {
        state->AddActor(&m_Cards[i]);
    }
}

bool net::Gamer::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_CARD_STATE_EVENT) {
        for (uint32_t i = 0; i < EVENT_MAX_NUM_CARD_STATES; i++) {
            CardState* state = &event.Data.AsCardStateEvent.States[i];
            printf("id=%d, value=%d, pos=(%f,%f)\n", state->Id, state->Value, state->X, state->Y);
            m_Cards[i].SetId(state->Id);
            m_Cards[i].SetValue(state->Value);
            m_Cards[i].SetPosition(state->X, state->Y);
        }
    }
    return false;
}

void net::Gamer::Update(float deltaSeconds)
{
    if (GetState()->GetFrameNumber() % 100 == 0) {
        GetGame()->GetNetworker()->SendServerEvent({ .EventType = NET_SERVER_REQUEST_CARD_STATE });
    }
}

void net::Gamer::Draw(net::Renderer* renderer)
{
}

void net::Gamer::DrawUI(net::Renderer* renderer)
{
}
