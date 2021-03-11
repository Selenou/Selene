#include "slnpch.h"
#include "DX11Device.h"

namespace Selene
{
	DX11Device::~DX11Device()
	{
		Destroy();
	}

	void DX11Device::Init(HWND windowHandle)
	{

        //TODO REWORK THIS
        //TODO REWORK THIS
        //TODO REWORK THIS
        //TODO REWORK THIS


        RECT clientRect;
        GetClientRect(windowHandle, &clientRect);
        LONG width = clientRect.right - clientRect.left;
        LONG height = clientRect.bottom - clientRect.top;

        SLN_ASSERT(windowHandle, "Window handle is null!");
        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = 1;    
        scd.BufferDesc.Width = width;
        scd.BufferDesc.Height = height;
        scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;    
        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        scd.BufferDesc.RefreshRate.Numerator = 0;
        scd.BufferDesc.RefreshRate.Denominator = 0;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   
        scd.Flags = 0;
        scd.OutputWindow = windowHandle;                               
        scd.SampleDesc.Count = 1;             
        scd.SampleDesc.Quality = 0;
        scd.Windowed = TRUE; 
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        D3D_FEATURE_LEVEL featureLevels = { D3D_FEATURE_LEVEL_11_0 };
        UINT createDeviceFlags = 0;

        // create a device, device context and swap chain using the information in the scd struct
        D3D11CreateDeviceAndSwapChain(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            createDeviceFlags,
            &featureLevels,
            1,
            D3D11_SDK_VERSION,
            &scd,
            &m_SwapChain,
            &m_Device,
            nullptr,
            &m_DeviceContext);

        
        ID3D11Texture2D* backBuffer;
        m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
        m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_Backbuffer);
        backBuffer->Release();
        m_DeviceContext->OMSetRenderTargets(1, &m_Backbuffer, nullptr);
	}

	void DX11Device::Destroy()
	{
        m_Backbuffer->Release();
		m_SwapChain->Release();
		m_Device->Release();
		m_DeviceContext->Release();
	}
}