#include "slnpch.h"
#include "DX11RenderingAPI.h"
#include "DX11Context.h"

namespace Selene 
{
	void DX11RenderingAPI::Init()
	{

	}

	void DX11RenderingAPI::Clear()
	{
		DX11Context* dx11Context = DX11Context::Get();
		dx11Context->GetDeviceContext()->ClearRenderTargetView(dx11Context->GetBackBuffer(), (float*)&m_ClearColor);
	}

	void DX11RenderingAPI::SetClearColor(const glm::vec4& color)
	{
		m_ClearColor = color;
	}

	void DX11RenderingAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		// TODO : Rework this when framebuffer is a thing
		
		//DX11Context* dx11Context = DX11Context::Get();

		// Release all outstanding references to the swap chain's buffers
		//dx11Context->GetDeviceContext()->OMSetRenderTargets(0, nullptr, nullptr);
		//auto ptr = dx11Context->GetBackBuffer();
		//ptr->Release();

		//THROW_DX11_FAILURE(dx11Context->GetSwapChain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
		// Get buffer
		//Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
		//THROW_DX11_FAILURE(dx11Context->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Resource), (void**)(&backBuffer)));

		// Create a render target view
		//auto renderTargetView = dx11Context->GetBackBuffer();
		//THROW_DX11_FAILURE(dx11Context->GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView));
		//dx11Context->GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
	}
}