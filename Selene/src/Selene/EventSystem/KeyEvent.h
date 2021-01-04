#pragma once

#include "Event.h"
#include "Selene/Core/KeyCodes.h"

namespace Selene
{
	class KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : " << m_KeyCode;
			return ss.str();
		}
	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}
	protected:
		KeyCode m_KeyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyCode keycode, const bool isHeld)
			: KeyEvent(keycode), m_IsHeld(isHeld) {}
	public:
		EVENT_TYPE(KeyPress)

		bool GetIsHeld() const { return m_IsHeld; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : " << m_KeyCode << " (Holding : " << m_IsHeld << ")";
			return ss.str();
		}
	private:
		bool m_IsHeld;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}
	public:
		EVENT_TYPE(KeyRelease)
	};

	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}
	public:
		EVENT_TYPE(KeyType)
	};
}