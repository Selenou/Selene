#pragma once

#include "Layer.h"

namespace Selene
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();
	public:
		void Update();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		std::vector<Layer*> m_Layers;
	};
}