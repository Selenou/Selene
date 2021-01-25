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
		virtual void DrawIndexedBaseVertex(uint32_t count, uint32_t offset) = 0;
	public:
		static std::unique_ptr<RenderingAPI> Create();
		static inline API GetAPI() { return s_API; }
		static inline void SetAPI(API api) { s_API = api; }
		static inline Info& GetInfo(){ return info; }
	private:
		static inline API s_API = RenderingAPI::API::None;
		static inline Info info = {};
	};
}