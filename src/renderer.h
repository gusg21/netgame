//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_RENDERER_H
#define NETGAME_RENDERER_H

#include <cstdint>
#include <raylib.h>

#include "color.h"
#include "eventqueue.h"
#include "rectangle.h"
#include "texture.h"

namespace net {
struct RendererSettings {
    uint32_t WindowWidth = 1600;
    uint32_t WindowHeight = 900;
    const char* WindowTitle = "Netgame";
	
	net::Color8 ClearColor = { 160, 217, 140, 255 };
};

class Renderer {
public:
    Renderer(const RendererSettings& config);
    Renderer(Renderer& renderer) = delete;
    Renderer(Renderer&& renderer) = delete;
    ~Renderer() = default;

    void DrawText(const char* text, int32_t fontSize, int32_t x, int32_t y, Color8 color);
    void DrawTextFormatted(const char* format, int32_t fontSize, int32_t x, int32_t y, Color8 color, ...);
    void DrawRectangle(net::Rectangle rect, Color8 color);
    void DrawRectangleLines(net::Rectangle rect, Color8 color);
    void DrawTextureRec(net::Texture tex, net::Rectangle srcRect, float x, float y, Color8 color);

    float GetTextWidth(const char* text, int32_t fontSize);
    float GetTextHeight(const char* text, int32_t fontSize);
    net::Vec2 ScreenToWorld(net::Vec2 screenPoint);

    void PostEvents(EventQueue* queue);
    void Begin();
    void End();
    void BeginWorldSpace();
    void EndWorldSpace();
    void Present();

private:
    Camera2D m_Camera;
    RenderTexture2D m_RenderTexture;
    Color8 m_ClearColor;

};
}

#endif