#include "slnpch.h"
#include "LayerStack.h"

namespace Selene
{
	LayerStack::LayerStack()
	{
		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Detach();
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

	void LayerStack::RenderUI()
	{
		m_ImGuiLayer->PrepareFrame();

		for (Layer* layer : m_Layers)
		{
			layer->RenderUI();
		}

		m_ImGuiLayer->RenderDrawData();
	}

	void LayerStack::PushLayer(Layer * layer)
	{
		layer->Attach();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer * layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			layer->Detach();
			m_Layers.erase(it);
		}
	}
}