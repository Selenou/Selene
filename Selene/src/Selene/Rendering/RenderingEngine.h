#pragma once

#include "RenderingAPI.h"

namespace Selene
{
	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
	private:
		static std::unique_ptr<RenderingAPI> s_RenderingAPI;
	};
}