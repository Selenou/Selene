#include "slnpch.h"
#include "DX11Context.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Selene
{
	void DX11Context::Init()
	{
		SLN_INFO("Initializing DX11 Rendering Context");
		m_Device->Init(glfwGetWin32Window(m_WindowHandle));

		// Get rendering info
		Microsoft::WRL::ComPtr<IDXGIFactory1> factory;
		THROW_DX11_FAILURE(CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)&factory));

		Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
		THROW_DX11_FAILURE(factory->EnumAdapters1(0, &adapter));

		DXGI_ADAPTER_DESC adapterDesc;
		THROW_DX11_FAILURE(adapter->GetDesc(&adapterDesc));

		// Renderer
		char renderer[128];
		WideCharToMultiByte(CP_ACP, 0, adapterDesc.Description, -1, renderer, 128, NULL, NULL);

		// Vendor
		std::string vendor;
		switch (adapterDesc.VendorId)
		{
			case 0x1002:	vendor = "AMD";					break;
			case 0x10DE:	vendor = "NVIDIA Corporation";  break;
			case 0x8086:	vendor = "Intel";				break;
			case 0x1414:	vendor = "Microsoft";			break;
			default:		vendor = "Unknown";				break;
		}

		// Version
		LARGE_INTEGER driverVersion;
		THROW_DX11_FAILURE(adapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &driverVersion));
		std::string version = std::to_string(HIWORD(driverVersion.HighPart)) + "." + std::to_string(LOWORD(driverVersion.HighPart)) + "." + std::to_string(HIWORD(driverVersion.LowPart)) + "." + std::to_string(LOWORD(driverVersion.LowPart));

		// Fill Rendering Info
		auto& info = RenderingAPI::GetInfo();
		info.API = "DX11";
		info.Version = version;
		info.Vendor = vendor;
		info.Renderer = renderer;
	}

	void DX11Context::SwapBuffers()
	{
		UINT isVsync = Game::GetInstance().GetWindow().IsVSync();
		THROW_DX11_FAILURE(m_Device->GetSwapChain()->Present(isVsync, 0));
	}
}