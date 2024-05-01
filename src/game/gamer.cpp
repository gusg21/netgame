#include "gamer.h"

#include "combineparts.h"

#include "../game.h"
#include "../networker.h"

net::Gamer::Gamer(net::State* lobbyState) 
    : m_Cards()
    , m_State(lobbyState)
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
            //printf("id=%d, value=%d, pos=(%f,%f)\n", state->Id, state->Value, state->X, state->Y);
            if (!m_Cards[i].IsHeld()) {
                m_Cards[i].SetId(state->Id);
                m_Cards[i].SetValue(state->Value);
                m_Cards[i].SetPosition(state->X, state->Y);
            }
            
        }
    }
    if (event.Type == EVENT_CARDS_COMBINED_EVENT) {
        GetState()->AddActor(new CombineParts(event.Data.AsCardsCombinedEvent.X, event.Data.AsCardsCombinedEvent.Y));
        for (uint32_t i = 0; i < EVENT_MAX_NUM_CARD_STATES; i++) {
            m_Cards[i].Drop();
        }
        
        return true;
    }
    if (event.Type == EVENT_GAME_FINISHED) {
        GetGame()->ChangeState(m_State);
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
