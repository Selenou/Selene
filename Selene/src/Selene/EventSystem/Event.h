#pragma once

#include "slnpch.h"

namespace Selene 
{
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		FramebufferResize,
		MouseButtonPress,
		MouseButtonRelease,
		KeyPress,
		KeyRelease,
		KeyType
	};

#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                         virtual EventType GetEventType() const override { return GetStaticType(); } \
                         virtual const char* GetName() const override { return #type; }

	class Event
	{
		friend class EventDispatcher;

	public:
		virtual ~Event() = default;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	protected:
		bool m_IsHandled = false;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}