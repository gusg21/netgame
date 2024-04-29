#include "renderer.h"
#include "eventqueue.h"
#include <cstdint>
#include <raylib.h>
#include <raymath.h>

// NOTE: Platform code is OK in this scope. Try to remove Raylib calls outside of this file!

#define COLOR8_TO_RAYCOLOR(color8)                     \
    ::Color                                            \
    {                                                  \
        (color8).r, (color8).g, (color8).b, (color8).a \
    }
#define NETRECT_TO_RAYRECT(rec)                     \
    ::Rectangle                                     \
    {                                               \
        (rec).X, (rec).Y, (rec).Width, (rec).Height \
    }

net::Renderer::Renderer(const RendererSettings& settings)
    : m_ClearColor(settings.ClearColor)
{
    InitWindow(settings.WindowWidth, settings.WindowHeight, settings.WindowTitle);
    // SetTargetFPS(60);

    m_Camera = {
        .offset = { .x = settings.WindowWidth / 2.f, .y = settings.WindowHeight / 2.f },
        .target = Vector2Zero(),
        .rotation = 0.f,
        .zoom = 2.f,
    };

    m_RenderTexture = LoadRenderTexture(settings.WindowWidth, settings.WindowHeight);
}

void net::Renderer::DrawText(const char* text, int32_t fontSize, int32_t x, int32_t y, Color8 color)
{
    ::DrawText(text, x, y, fontSize, COLOR8_TO_RAYCOLOR(color));
}

void net::Renderer::DrawTextFormatted(const char* format, int32_t fontSize, int32_t x, int32_t y, Color8 color, ...)
{
    char text[1024] = { 0 };
    va_list args;
    va_start(args, color);
    vsnprintf(text, 1024, format, args);
    va_end(args);
    ::DrawText(text, x, y, fontSize, COLOR8_TO_RAYCOLOR(color));
}

void net::Renderer::DrawRectangle(net::Rectangle rect, net::Color8 color)
{
    ::DrawRectangle(rect.X, rect.Y, rect.Width, rect.Height, COLOR8_TO_RAYCOLOR(color));
}

void net::Renderer::DrawRectangleLines(net::Rectangle rect, Color8 color)
{
    ::DrawRectangleLines(rect.X, rect.Y, rect.Width, rect.Height, COLOR8_TO_RAYCOLOR(color));
}

void net::Renderer::DrawTextureRec(net::Texture tex, net::Rectangle srcRect, float x, float y, Color8 color)
{
    ::DrawTextureRec(*(Texture2D*)tex.GetTextureHandle(), NETRECT_TO_RAYRECT(srcRect), { x, y }, COLOR8_TO_RAYCOLOR(color));
}

float net::Renderer::GetTextWidth(const char* text, int32_t fontSize)
{
    return ::MeasureText(text, fontSize);
}

float net::Renderer::GetTextHeight(const char* text, int32_t fontSize)
{
    return ::MeasureTextEx(GetFontDefault(), text, fontSize, 1.f).y;
}

net::Vec2 net::Renderer::ScreenToWorld(net::Vec2 screenPoint)
{
    ::Vector2 worldPoint = ::GetScreenToWorld2D({ screenPoint.X, screenPoint.Y }, m_Camera);
    return { worldPoint.x, worldPoint.y };
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
    ::DrawTextureRec(
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
