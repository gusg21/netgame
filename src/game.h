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

namespace net {
class Game {
public:
    Game(const RendererSettings& settings);

    net::State* NewState();
    void RunGame(net::State* initialState);

private:
    net::Networker m_Networker;
    net::Renderer m_Renderer;
    net::EventQueue m_EventQueue;

    std::array<net::State, 16> m_States;
    uint32_t m_NextStateIndex = 0;
    net::State* m_CurrentState = nullptr;
};
}

#endif // NETGAME_GAME_H