#pragma once

#include "slnpch.h"
#include "Selene/EventSystem/Event.h"

namespace Selene 
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			:m_Name(name) {}
		virtual ~Layer() = default;
	public:
		virtual void Attach() {}
		virtual void Detach() {}
		virtual void Update() {}
		virtual void RenderUI() {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}