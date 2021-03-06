#pragma once

#include "slnpch.h"

#include "Selene/Event/Event.h"
#include "Selene/Config.h"
#include "Selene/Rendering/Context.h"

namespace Selene 
{
	struct WindowSettings
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowSettings(const std::string& title = Config::DEFAULT_WINDOW_NAME,
				   uint32_t width = Config::DEFAULT_WINDOW_WIDTH,
				   uint32_t height = Config::DEFAULT_WINDOW_HEIGHT)
			: Title(title), Width(width), Height(height){}
	};

	class Window
	{
	public:
		virtual ~Window() = default;
	public:
		using EventCallback = std::function<void(Event&)>;
		virtual void SwapBuffers() = 0;
		virtual void PollEvents() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual Context* GetRenderingContext() = 0;
		static Window* Create(const WindowSettings& props = WindowSettings());
	protected:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
	};
}