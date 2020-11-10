#pragma once

#include "Layer.h"
#include "ImGui/ImGuiLayer.h"

namespace Selene
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
	public:
		void Update();
		void RenderUI();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		std::vector<Layer*> m_Layers;
		ImGuiLayer* m_ImGuiLayer;
	};
}