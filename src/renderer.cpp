#include "renderer.h"
#include <raylib.h>
#include <raymath.h>
#include <cstdint>

net::Renderer::Renderer(const RendererSettings& settings)
{
	InitWindow(settings.WindowWidth, settings.WindowHeight, settings.WindowTitle);

	m_Camera = {
			.offset = {.x = settings.WindowWidth / 2.f, .y = settings.WindowHeight / 2.f},
			.target = Vector2Zero(),
			.rotation = 0.f,
			.zoom = 2.f,
	};

	m_RenderTexture = LoadRenderTexture(settings.WindowWidth, settings.WindowHeight);
}

void net::Renderer::Begin()
{
	BeginDrawing();

	ClearBackground(Color(124, 194, 100, 255));

	BeginTextureMode(m_RenderTexture);
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
	DrawTextureRec(m_RenderTexture.texture, { 0, 0, (float)m_RenderTexture.texture.width, (float)m_RenderTexture.texture.height }, { 0, 0 }, WHITE);

	EndDrawing();
}
