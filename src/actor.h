//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_ACTOR_H
#define NETGAME_ACTOR_H

#include <iostream>

#include "renderer.h"
#include "../state.h" // May eventually not be a sustainable relationship

namespace net {
class State;

class Actor {
public:
    Actor() = default;
    Actor(const Actor& actor) = delete;
    Actor(Actor&& actor) = delete;
    ~Actor() { std::cout << "Actor Destroyed" << std::endl; }

    void SetState(net::State* state) { m_State = state; }

    virtual bool HandleEvent(net::Event event) { return false; };
    virtual void PreUpdate(float deltaSeconds) {};
    virtual void Update(float deltaSeconds) {};
    virtual void Draw(net::Renderer* renderer) {};
    virtual void DrawUI(net::Renderer* renderer) {};

    [[nodiscard]] bool IsAlive() const { return m_Alive; }
    void Revive() { m_Alive = true; }
    void Kill() { m_Alive = false; }

protected:
    [[nodiscard]] net::State* GetState() const { return m_State; }
    [[nodiscard]] net::Game* GetGame() const { return m_State->GetGame(); } // The only reason we need the class def for State

private:
    net::State* m_State = nullptr;
    bool m_Alive = false;
};
} // namespace net

#endif // NETGAME_ACTOR_H
