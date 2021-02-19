#pragma once

#include "Selene/Core/Layer.h"
#include "RenderingPanel.h"

namespace Selene
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {}
		~ImGuiLayer() = default;
	public:
		virtual void Attach() override;
		virtual void Detach() override;
		virtual void RenderUI() override;
		void StartNewFrame();
		void EndFrame();
	private:
		RenderingPanel m_RenderingPanel;
	};
}