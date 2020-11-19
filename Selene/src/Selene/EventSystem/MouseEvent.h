#pragma once

#include "Event.h"
#include "Selene/KeyCodes.h"

namespace Selene
{
	class MouseButtonEvent : public Event
	{
	public:
		inline KeyCode GetMouseButton() { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : " << m_Button;
			return ss.str();
		}
	protected:
		MouseButtonEvent(const KeyCode button)
			: m_Button(button) {}
	protected:
		KeyCode m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(const KeyCode button)
			: MouseButtonEvent(button) {}
	public:
		EVENT_TYPE(MouseButtonPress)
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(const KeyCode button)
			: MouseButtonEvent(button) {}
	public:
		EVENT_TYPE(MouseButtonRelease)
	};
}