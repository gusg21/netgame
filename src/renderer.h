//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_RENDERER_H
#define NETGAME_RENDERER_H

#include <raylib.h>
#include <cstdint>

namespace net {
	struct RendererSettings {
		uint32_t WindowWidth;
		uint32_t WindowHeight;
		const char* WindowTitle;
	};

	class Renderer {
	public:
		Renderer(const RendererSettings& config);
		Renderer(Renderer& renderer) = delete;
		Renderer(Renderer&& renderer) = delete;
		~Renderer() = default;

		void Begin();
		void End();
		void Present();

	private:
		Camera2D m_Camera;
		RenderTexture2D m_RenderTexture;
	};
}

#endif