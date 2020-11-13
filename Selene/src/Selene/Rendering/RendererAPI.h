#pragma once

namespace Selene 
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL,
			Vulkan
		};
	public:
		virtual ~RendererAPI() = default;
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;

		static API GetAPI() { return s_API; }
		static void SetAPI(API api) { s_API = api; }
	private:
		static API s_API;
	};
}