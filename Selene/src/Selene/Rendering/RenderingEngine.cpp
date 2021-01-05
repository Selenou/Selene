#include "slnpch.h"
#include "RenderingEngine.h"

namespace Selene
{
	std::unique_ptr<RenderingAPI> RenderingEngine::s_RenderingAPI = nullptr;

	void RenderingEngine::Init()
	{
		s_RenderingAPI = RenderingAPI::Create();
		s_RenderingAPI->Init();
	}

	void RenderingEngine::Clear()
	{
		s_RenderingAPI->Clear();
	}

	void RenderingEngine::SetViewport(uint32_t width, uint32_t height)
	{
		s_RenderingAPI->SetViewport(0, 0, width, height);
	}

	void RenderingEngine::DrawIndexed(uint32_t count)
	{
		s_RenderingAPI->DrawIndexed(count);
	}
}