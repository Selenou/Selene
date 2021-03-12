#pragma once

#include "Selene/Rendering/RenderingAPI.h"

namespace Selene
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(uint32_t count) override;
		virtual void DrawIndexedBaseVertex(uint32_t count, uint32_t offset) override;
		virtual void DrawInstanced(uint32_t indiceCount, uint32_t instanceCount) override;
	};
}