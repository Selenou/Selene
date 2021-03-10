#pragma once

#include "Selene/UI/ImGuiLayer.h"

namespace Selene
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Attach() override;
		virtual void Detach() override;
		virtual void StartNewFrame() override;
		virtual void EndFrame() override;
	};
}