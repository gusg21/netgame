#include "state.h"
#include "actor.h"
#include <memory>

net::State::State()
    : m_Actors()
    , m_NextActorIndex(0)
    , m_Valid(false)
{
}

void net::State::HandleEvents(net::EventQueue* events)
{
    events->ResetEventReadHead();
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        if (m_Actors[i] != nullptr) {
            Event event = events->GetNextEvent();
            while (event.Type != EVENT_NONE_EVENT) {
                if (m_Actors[i]->HandleEvent(event)) {
                    events->HandleThisEvent();
                }
                event = events->GetNextEvent();
            }
            events->ResetEventReadHead();
        }
    }
}

void net::State::Update(float deltaSeconds)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        if (m_Actors[i] != nullptr)
            m_Actors[i]->Update(deltaSeconds);
    }
    m_FrameNumber++;
    m_ElapsedTime += deltaSeconds;
}

void net::State::Draw(net::Renderer* renderer)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        if (m_Actors[i] != nullptr)
            m_Actors[i]->Draw(renderer);
    }
}

void net::State::AddActor(Actor* actor)
{
    m_Actors[m_NextActorIndex] = actor;
    m_NextActorIndex++;

    actor->SetState(this);
}
void net::State::DrawUI(net::Renderer* renderer)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        if (m_Actors[i] != nullptr)
            m_Actors[i]->DrawUI(renderer);
    }
}
