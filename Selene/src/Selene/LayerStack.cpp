#include "slnpch.h"
#include "LayerStack.h"

namespace Selene
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->UnBind();
			delete layer;
		}
	}

	void LayerStack::Update()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Update();
		}
	}

	void LayerStack::PushLayer(Layer * layer)
	{
		layer->Bind();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer * layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			layer->UnBind();
			m_Layers.erase(it);
		}
	}
}