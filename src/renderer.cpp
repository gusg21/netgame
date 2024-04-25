#include "renderer.h"
#include <cstdint>
#include <raylib.h>
#include <raymath.h>
#include "eventqueue.h"

// NOTE: Platform code is OK in this scope. Try to remove Raylib calls outside of this file!

net::Renderer::Renderer(const RendererSettings& settings) : m_ClearColor(settings.ClearColor)
{
    InitWindow(settings.WindowWidth, settings.WindowHeight, settings.WindowTitle);

    m_Camera = {
        .offset = { .x = settings.WindowWidth / 2.f, .y = settings.WindowHeight / 2.f },
        .target = Vector2Zero(),
        .rotation = 0.f,
        .zoom = 2.f,
    };

    m_RenderTexture = LoadRenderTexture(settings.WindowWidth, settings.WindowHeight);
}

void net::Renderer::PostEvents(net::EventQueue* queue)
{
	if (WindowShouldClose())
		queue->PostEvent({ .Type = EVENT_QUIT_EVENT });
}

void net::Renderer::Begin()
{
    BeginDrawing();

    ClearBackground({ 210, 100, 90, 255 }); // Debug Red

    BeginTextureMode(m_RenderTexture);

    ClearBackground({ m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a });

    BeginMode2D(m_Camera);
}

void net::Renderer::End()
{
    EndMode2D();
    EndTextureMode();

    DrawFPS(10, 10);
}

void net::Renderer::Present()
{
    DrawTextureRec(
        m_RenderTexture.texture,
        { 0, 0, (float)m_RenderTexture.texture.width, -(float)m_RenderTexture.texture.height },
        { 0, 0 },
        WHITE);

    EndDrawing();
}
