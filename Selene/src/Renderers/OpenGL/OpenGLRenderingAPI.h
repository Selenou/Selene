#pragma once

#include "Selene/Rendering/RenderingAPI.h"

namespace Selene
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(uint32_t count) override;
	};
}