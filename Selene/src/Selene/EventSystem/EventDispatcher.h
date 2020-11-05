#pragma once

#include "slnpch.h"
#include "Event.h"

namespace Selene
{
	class EventDispatcher 
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) 
		{
		}

		template<class T, class F>
		bool Dispatch(const F& func)
		{
			if (!m_Event.m_IsHandled && 
				m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_IsHandled |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};
}