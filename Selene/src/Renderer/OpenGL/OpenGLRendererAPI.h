#pragma once

#include "Selene/Rendering/RendererAPI.h"

namespace Selene
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Clear() override;
	};
}