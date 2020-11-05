#pragma once

#include "slnpch.h"

#include "EventSystem/Event.h"

namespace Selene 
{
	struct WindowSettings
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowSettings(const std::string& title = "Selene Engine",
				   uint32_t width = 1280,
				   uint32_t height = 720) 
			: Title(title), Width(width), Height(height){}
	};

	class Window
	{
	public:
		virtual ~Window() {};
	public:
		using EventCallback = std::function<void(Event&)>;
		virtual void Update() = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		static Window* Create(const WindowSettings& props = WindowSettings());
	protected:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
	};
}