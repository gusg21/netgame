#include "game.h"

#include "renderer.h"

net::Game::Game(const RendererSettings& settings)
    : m_Renderer(settings)
    , m_Networker()
    , m_Input()
    , m_EventQueue()
    , m_States()
{
}

net::State* net::Game::NewState()
{
    net::State* state = &m_States[m_NextStateIndex++];

    state->SetValidity(true);
    state->SetGame(this);

    return state;
}

void net::Game::RunGame(net::State* initialState)
{
    m_CurrentState = initialState;
    uint32_t frameNumber = 0;

    bool shouldQuit = false;
    while (!shouldQuit) {
        m_CurrentState->PreUpdate(GetFrameTime());

        m_EventQueue.ClearEvents();
        m_Renderer.PostEvents(&m_EventQueue);
        m_Input.PostEvents(&m_EventQueue);
        m_Networker.PostGameEvents(&m_EventQueue);

        // Process events
        Event event = m_EventQueue.GetNextEvent();
        while (event.Type != EVENT_NONE_EVENT) {
            if (event.Type == EVENT_QUIT_EVENT) {
                m_EventQueue.HandleThisEvent();
                shouldQuit = true;
                printf("Quitting gracefully...\n");
            }

            event = m_EventQueue.GetNextEvent();
        }
        m_EventQueue.ResetEventReadHead();

        m_CurrentState->HandleEvents(&m_EventQueue);

        // Update game state
        m_CurrentState->Update(GetFrameTime());

        // Drawing
        m_Renderer.Begin();
        {
            m_Renderer.BeginWorldSpace();
            {
                m_CurrentState->Draw(&m_Renderer);
            }
            m_Renderer.EndWorldSpace();

            m_CurrentState->DrawUI(&m_Renderer);
        }
        m_Renderer.End();

        m_Renderer.Present();

        frameNumber++;
    }
}
