//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_GAME_H
#define NETGAME_GAME_H

#include <array>

#include "eventqueue.h"
#include "networker.h"
#include "renderer.h"
#include "state.h"
#include "input.h"

namespace net {
class Game {
public:
    Game(const RendererSettings& settings);

    net::State* NewState();
    void ChangeState(net::State* state);
    void RunGame(net::State* initialState);

    [[nodiscard]] net::Networker* GetNetworker() /* const */ { return &m_Networker; }
    [[nodiscard]] net::Renderer* GetRenderer() /* const */ { return &m_Renderer; }

private:
    net::Networker m_Networker;
    net::Renderer m_Renderer;
    net::Input m_Input;
    net::EventQueue m_EventQueue;

    std::array<net::State, 16> m_States;
    uint32_t m_NextStateIndex = 0;
    net::State* m_CurrentState = nullptr;
    net::State* m_NextState = nullptr;
};
}

#endif // NETGAME_GAME_H