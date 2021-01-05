#pragma once

#include "RenderingAPI.h"

namespace Selene
{
	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static void SetViewport(uint32_t width, uint32_t height);
		static void DrawIndexed(uint32_t count);
		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
	private:
		static std::unique_ptr<RenderingAPI> s_RenderingAPI;
	};
}