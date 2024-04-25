#include "game.h"

#include "renderer.h"

net::Game::Game(const RendererSettings& settings)
    : m_Renderer(settings)
    , m_Networker()
    , m_States()
{
}

net::State* net::Game::NewState()
{
    net::State* state = &m_States[m_NextStateIndex++];

    state->SetValidity(true);

    return state;
}

void net::Game::RunGame(net::State* initialState)
{
    m_CurrentState = initialState;

    bool shouldQuit = false;
    while (!shouldQuit) {
		// Process events
		Event event = m_EventQueue.GetNextEvent();
		while (event.Type != EVENT_NONE) {
			if (event.Type == EVENT_QUIT_EVENT) {
				m_EventQueue.HandleThisEvent();
				shouldQuit = true;
			}

			event = m_EventQueue.GetNextEvent();
		}
		m_EventQueue.ResetEventReadHead();

		m_CurrentState->HandleEvents(&m_EventQueue);

		// Update game state
        m_CurrentState->Update();

        // Drawing
        m_Renderer.Begin();
        {
            m_CurrentState->Draw(&m_Renderer);
        }
        m_Renderer.End();

        m_Renderer.Present();

		m_Renderer.PostEvents(&m_EventQueue);
    }
}
