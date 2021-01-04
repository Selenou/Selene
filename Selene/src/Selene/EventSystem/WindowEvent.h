#pragma once

#include "Event.h"

namespace Selene 
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowClose)
	};

	// The window size is in screen coordinates
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}
	public:
		EVENT_TYPE(WindowResize)

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " : (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	// The size of the framebuffer is in pixels coordinates and may change independently of the size of a window
	// On some machines screen coordinates and pixels are the same, but on others they will not be (Ex : Retina displays).
	class FramebufferResizeEvent : public Event
	{
	public:
		FramebufferResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}
	public:
		EVENT_TYPE(FramebufferResize)

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
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