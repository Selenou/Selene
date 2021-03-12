#pragma once
#include <d3d11.h>

namespace Selene
{
	class DX11Device
	{
	public:
		DX11Device() = default;
		~DX11Device();
	public:
		void Init(HWND windowHandle);
		void Destroy();
	public:
		inline ID3D11Device* GetDevice() { return m_Device; }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext; }
		inline IDXGISwapChain* GetSwapChain() { return m_SwapChain; }
		inline ID3D11RenderTargetView* GetBackBuffer() { return m_Backbuffer; }
	private:
		ID3D11Device* m_Device = nullptr; // Virtual representation of the video adapter                  
		ID3D11DeviceContext* m_DeviceContext = nullptr; // Responsible for managing the GPU and the rendering pipeline
		IDXGISwapChain* m_SwapChain = nullptr;
		ID3D11RenderTargetView* m_Backbuffer = nullptr;
	};
}