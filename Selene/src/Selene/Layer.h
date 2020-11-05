#pragma once

#include "slnpch.h"
#include "EventSystem/Event.h"

namespace Selene 
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			:m_Name(name) {}
		virtual ~Layer() = default;
	public:
		virtual void Bind() {}
		virtual void UnBind() {}
		virtual void Update() {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}