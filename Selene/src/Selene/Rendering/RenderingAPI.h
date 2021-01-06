#pragma once

namespace Selene 
{
	class RenderingAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL,
			Vulkan
		};

		struct Info
		{
			std::string API;
			std::string Vendor;
			std::string Renderer;
			std::string Version;
			std::string ShadingLanguageVersion;
		};
	public:
		virtual ~RenderingAPI() = default;
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void DrawIndexed(uint32_t count) = 0;

		static API GetAPI() { return s_API; }
		static void SetAPI(API api) { s_API = api; }

		static Info& GetInfo() 
		{ 
			static Info info;
			return info;
		}

		static std::unique_ptr<RenderingAPI> Create();
	private:
		static API s_API;
	};
}