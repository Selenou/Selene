#pragma once

#include "Selene/Rendering/RenderingAPI.h"

namespace Selene
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		void Init() override;
		void Clear() override;
	};
}