#include "renderer.h"
#include <cstdint>
#include <raylib.h>
#include <raymath.h>
#include "eventqueue.h"

// NOTE: Platform code is OK in this scope. Try to remove Raylib calls outside of this file!

net::Renderer::Renderer(const RendererSettings& settings) : m_ClearColor(settings.ClearColor)
{
    InitWindow(settings.WindowWidth, settings.WindowHeight, settings.WindowTitle);
    //SetTargetFPS(60);

    m_Camera = {
        .offset = { .x = settings.WindowWidth / 2.f, .y = settings.WindowHeight / 2.f },
        .target = Vector2Zero(),
        .rotation = 0.f,
        .zoom = 2.f,
    };

    m_RenderTexture = LoadRenderTexture(settings.WindowWidth, settings.WindowHeight);
}

void net::Renderer::DrawText(const char* text, int32_t x, int32_t y, Color8 color)
{
    ::DrawText(text, x, y, 10, { color.r, color.g, color.b, color.a });
}

void net::Renderer::DrawTextFormatted(const char* format, int32_t x, int32_t y, Color8 color, ...)
{
    char text[1024] = {0};
    va_list args;
    va_start(args, color);
    vsnprintf(text, 1024, format, args);
    va_end(args);
    ::DrawText(text, x, y, 10, { color.r, color.g, color.b, color.a });
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
}

void net::Renderer::End()
{
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
void net::Renderer::BeginWorldSpace()
{
    BeginMode2D(m_Camera);
}
void net::Renderer::EndWorldSpace()
{
    EndMode2D();
}
