#include "state.h"
#include "actor.h"
#include <memory>

net::State::State()
    : m_Actors()
    , m_NextActorIndex(0)
    , m_Valid(false)
    , m_Game(nullptr)
{
}

void net::State::Initialize(net::Game* game)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr)
            actor->Initialize(this);
    }
}

void net::State::HandleEvents(net::EventQueue* events)
{
    events->ResetEventReadHead();
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr) {
            if (actor->IsAlive()) {
                Event event = events->GetNextEvent();
                while (event.Type != EVENT_NONE_EVENT) {
                    if (actor->HandleEvent(event)) {
                        events->HandleThisEvent();
                    }
                    event = events->GetNextEvent();
                }
                events->ResetEventReadHead();
            }
        }
    }
}

void net::State::PreUpdate(float deltaSeconds)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr)
            if (actor->IsAlive())
                actor->PreUpdate(deltaSeconds);
    }
}

void net::State::Update(float deltaSeconds)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr)
            if (actor->IsAlive())
                actor->Update(deltaSeconds);
    }
    m_FrameNumber++;
    m_ElapsedTime += deltaSeconds;
}

void net::State::Draw(net::Renderer* renderer)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr)
            if (actor->IsAlive())
                actor->Draw(renderer);
    }
}

void net::State::DrawUI(net::Renderer* renderer)
{
    for (uint32_t i = 0; i < STATE_MAX_ACTORS; i++) {
        Actor* actor = m_Actors[i];
        if (actor != nullptr)
            if (actor->IsAlive())
                actor->DrawUI(renderer);
    }
}

void net::State::AddActor(Actor* actor)
{
    m_Actors[m_NextActorIndex] = actor;
    m_NextActorIndex++;

    actor->Revive();
}
