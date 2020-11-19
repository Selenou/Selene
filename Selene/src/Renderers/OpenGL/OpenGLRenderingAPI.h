#pragma once

#include "Selene/Rendering/RenderingAPI.h"

namespace Selene
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		void Init() override;
		void Clear() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}