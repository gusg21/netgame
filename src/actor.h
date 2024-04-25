//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_ACTOR_H
#define NETGAME_ACTOR_H

#include <iostream>

#include "renderer.h"

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
    virtual void Update() {};
    virtual void Draw(net::Renderer* renderer) {};

    bool IsAlive() const { return m_Alive; }

protected:
    [[nodiscard]] net::State* GetState() { return m_State; }

private:
    net::State* m_State = nullptr;
    bool m_Alive = false;
};
} // namespace net

#endif // NETGAME_ACTOR_H
