#pragma once

#include "Event.h"

namespace Selene 
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}
	public:
		EVENT_TYPE(WindowResize)

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};
}