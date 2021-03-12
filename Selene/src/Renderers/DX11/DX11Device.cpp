#include "slnpch.h"
#include "DX11Device.h"

namespace Selene
{
	void DX11Device::Init(HWND windowHandle)
	{
        SLN_ASSERT(windowHandle, "Window handle is null!");

        DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
        swapChainDescription.BufferDesc.Width                   = 0;
        swapChainDescription.BufferDesc.Height                  = 0;
        swapChainDescription.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDescription.BufferDesc.RefreshRate.Numerator   = 0;
        swapChainDescription.BufferDesc.RefreshRate.Denominator = 0;
        swapChainDescription.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDescription.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDescription.SampleDesc.Count                   = 1; 
        swapChainDescription.SampleDesc.Quality                 = 0; 
        swapChainDescription.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDescription.BufferCount                        = 1; // 1 back bufer = double buffering (front + back)
        swapChainDescription.OutputWindow                       = windowHandle;
        swapChainDescription.Windowed                           = TRUE;
        swapChainDescription.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDescription.Flags                              = 0;

        D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &swapChainDescription,
            &m_SwapChain,
            &m_Device,
            nullptr,
            &m_DeviceContext
        );

        // Get the address of the back buffer
        Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
        m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)(&backBuffer));

        // Use the back buffer address to create the render target
        SLN_ASSERT(backBuffer, "Back buffer is null!");
        m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_Backbuffer.GetAddressOf());

        // Set the render target as the back buffer
        m_DeviceContext->OMSetRenderTargets(1, m_Backbuffer.GetAddressOf(), nullptr);
	}
}