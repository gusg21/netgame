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
    void Update(float deltaSeconds);
    void Draw(net::Renderer* renderer);
    void DrawUI(net::Renderer* renderer);

    bool GetValidity() { return m_Valid; }
    void SetValidity(bool valid) { m_Valid = valid; }

    [[nodiscard]] uint32_t GetFrameNumber() const { return m_FrameNumber; };
    [[nodiscard]] float GetElapsedTime() const { return m_ElapsedTime; };

    void AddActor(Actor* actor);

private:
    bool m_Valid = false;
    uint32_t m_FrameNumber = 0;
    float m_ElapsedTime = 0.f;

    std::array<Actor*, STATE_MAX_ACTORS> m_Actors;
    uint32_t m_NextActorIndex = 0;
};
}