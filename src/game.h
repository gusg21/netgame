//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_GAME_H
#define NETGAME_GAME_H

#include <array>

#include "game/networker.h"
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

		std::array<net::State, 16> m_States;
		uint32_t m_NextStateIndex = 0;
	};
}

#endif // NETGAME_GAME_H