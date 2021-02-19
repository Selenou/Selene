#pragma once

#include "Event.h"
#include "Selene/Core/KeyCodes.h"

namespace Selene
{
	class MouseButtonEvent : public Event
	{
	public:
		inline KeyCode GetMouseButton() { return m_Button; }

		virtual std::string ToString() const override
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

	class MousePositionMoveEvent : public Event
	{
	public:
		MousePositionMoveEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}
	public:
		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	public:
		EVENT_TYPE(MousePositionMove)
	private:
		float m_MouseX, m_MouseY;
	};
}