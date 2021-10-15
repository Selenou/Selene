#pragma once

#include "Layer.h"
#include "Selene/UI/ImGuiLayer.h"

namespace Selene
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
	public:
		void Update(Timestep ts);
		void Render();
		void HandleEvent(Event& event);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);
	private:
		std::vector<Layer*> m_Layers;
		ImGuiLayer* m_ImGuiLayer;
		uint32_t m_LayerInsertIndex = 0;
		bool m_HasOverlay = false;
	};
}