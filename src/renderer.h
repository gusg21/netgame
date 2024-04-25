//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_RENDERER_H
#define NETGAME_RENDERER_H

#include <cstdint>
#include <raylib.h>

#include "color.h"
#include "eventqueue.h"

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

    void PostEvents(net::EventQueue* queue);
    void Begin();
    void End();
    void Present();

private:
    Camera2D m_Camera;
    RenderTexture2D m_RenderTexture;
    net::Color8 m_ClearColor;
};
}

#endif