#pragma once

#include "DX11.h"

namespace Selene
{
	class DX11Device
	{
	public:
		DX11Device() = default;
	public:
		void Init(HWND windowHandle);
	public:
		inline ID3D11Device* GetDevice() { return m_Device.Get(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext.Get(); }
		inline IDXGISwapChain* GetSwapChain() { return m_SwapChain.Get(); }
		inline ID3D11RenderTargetView* GetBackBuffer() { return m_Backbuffer.Get(); }
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr; // Virtual representation of the video adapter                  
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext = nullptr; // Responsible for managing the GPU and the rendering pipeline
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_Backbuffer = nullptr;
	};
}