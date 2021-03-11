#include "slnpch.h"
#include "DX11RenderingAPI.h"
#include "Selene/Config.h"

namespace Selene 
{
	void DX11RenderingAPI::Init()
	{
		// Fill Rendering Info
		auto& info = RenderingAPI::GetInfo();
		info.API = "DX11";
		//info.Vendor = (const char*)glGetString(GL_VENDOR);
		//info.Renderer = (const char*)glGetString(GL_RENDERER);
		//info.Version = (const char*)glGetString(GL_VERSION);
		//info.ShadingLanguageVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void DX11RenderingAPI::Clear()
	{
		//devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));
	}

	void DX11RenderingAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		//glViewport(x, y, width, height);
	}
}