#include "slnpch.h"
#include "LayerStack.h"

namespace Selene
{
	LayerStack::LayerStack()
	{
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Detach();
			delete layer;
		}
	}

	void LayerStack::Update(Timestep ts)
	{
		for (Layer* layer : m_Layers)
		{
			layer->Update(ts);
		}
	}

	void LayerStack::Render()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Render();
		}

		// UI
		m_ImGuiLayer->StartNewFrame();
		{
			for (Layer* layer : m_Layers)
			{
				layer->RenderUI();
			}
		}
		m_ImGuiLayer->EndFrame();
	}

	void LayerStack::HandleEvent(Event& event)
	{
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnEvent(event);

			if(event.IsHandled())
				break;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->Attach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			layer->Detach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->Attach();
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			layer->Detach();
			m_Layers.erase(it);
		}
	}
}