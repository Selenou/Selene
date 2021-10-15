#pragma once

#include <glm/vec4.hpp>

namespace Selene 
{
	class RenderingAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL
		};

		struct Info
		{
			std::string API;
			std::string Version;
			std::string Vendor;
			std::string Renderer;
		};
	public:
		virtual ~RenderingAPI() = default;
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void DrawIndexed(uint32_t count) = 0;
		virtual void DrawIndexedBaseVertex(uint32_t count, uint32_t offset) = 0;
		virtual void DrawInstanced(uint32_t indiceCount, uint32_t instanceCount) = 0;
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