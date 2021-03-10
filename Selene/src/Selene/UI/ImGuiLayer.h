#pragma once

#include "Selene/Core/Layer.h"

namespace Selene
{
	class ImGuiLayer : public Layer
	{
	public:
		static ImGuiLayer* Create();
	public:
		virtual void Attach() override = 0;
		virtual void Detach() = 0; 
	public:
		virtual void StartNewFrame() = 0;
		virtual void EndFrame() = 0;
	public:
		virtual void RenderUI() override;
	protected:
		ImGuiLayer() : Layer("ImGui") {}
	};
}