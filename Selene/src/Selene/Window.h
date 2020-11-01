#pragma once

#include "slnpch.h"

namespace Selene {

	struct WindowData
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowData(
			const std::string& title = "Selene Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		virtual ~Window() {};
	public:
		virtual void Init(const WindowData& data) = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
		virtual void SetVSync(bool enabled) = 0;
		static Window* Create(const WindowData& props = WindowData());
	protected:
		WindowData m_Data;
	};
}