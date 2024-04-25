#pragma once
#include <array>
#include <memory>

#include "actor.h"
#include "renderer.h"

#define STATE_MAX_ACTORS 128

namespace net {
class State {
public:
    State();

	void HandleEvents(net::EventQueue* events);
    void Update();
    void Draw(net::Renderer* renderer);

    bool GetValidity() { return m_Valid; }
    void SetValidity(bool valid) { m_Valid = valid; }

    void AddActor(Actor* actor);

private:
    bool m_Valid = false;

    std::array<Actor*, STATE_MAX_ACTORS> m_Actors;
    uint32_t m_NextActorIndex = 0;
};
}