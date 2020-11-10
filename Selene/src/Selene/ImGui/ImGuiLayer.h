#pragma once

#include "Selene/Layer.h"

namespace Selene
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {};
		~ImGuiLayer() = default;
	public:
		void Attach() override;
		void Detach() override;
		void RenderUI() override;
		void PrepareFrame();
		void RenderDrawData();
	};
}