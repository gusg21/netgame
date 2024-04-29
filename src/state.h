#pragma once
#include <array>
#include <memory>

#define STATE_MAX_ACTORS 128

namespace net {
class Actor;
class Game;
class Renderer;
class EventQueue;

class State {
public:
    State();

    void Initialize(net::Game* game);
    void HandleEvents(net::EventQueue* events);
    void PreUpdate(float deltaSeconds);
    void Update(float deltaSeconds);
    void Draw(net::Renderer* renderer);
    void DrawUI(net::Renderer* renderer);

    [[nodiscard]] bool GetValidity() const { return m_Valid; }
    void SetValidity(bool valid) { m_Valid = valid; }
    [[nodiscard]] net::Game* GetGame() const { return m_Game; }
    void SetGame(net::Game* game) { m_Game = game; }

    [[nodiscard]] uint32_t GetFrameNumber() const { return m_FrameNumber; }
    [[nodiscard]] float GetElapsedTime() const { return m_ElapsedTime; }

    void AddActor(Actor* actor);

private:
    bool m_Valid = false;
    uint32_t m_FrameNumber = 0;
    float m_ElapsedTime = 0.f;

    net::Game* m_Game;

    std::array<net::Actor*, STATE_MAX_ACTORS> m_Actors;
    uint32_t m_NextActorIndex = 0;
};
}