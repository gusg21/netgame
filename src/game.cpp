#include "game.h"

#include "renderer.h"

net::Game::Game(const RendererSettings& settings) : m_Renderer(settings), m_Networker() {
}

net::State* net::Game::NewState() {
	net::State* state = &m_States[m_NextStateIndex++];

	state->SetValidity(true);

	return state;
}

void net::Game::RunGame(net::State* initialState) {
	bool shouldQuit = false;
	while (!shouldQuit) {

		// Drawing
		m_Renderer.Begin();

		m_Renderer.End();

		m_Renderer.Present();
	}
}
