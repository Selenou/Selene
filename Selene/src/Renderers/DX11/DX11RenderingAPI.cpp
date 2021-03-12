#include "slnpch.h"
#include "DX11RenderingAPI.h"
#include "Selene/Config.h"
#include "DX11Context.h"

namespace Selene 
{
	void DX11RenderingAPI::Init()
	{
		IDXGIFactory* factory = nullptr;
		CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

		IDXGIAdapter* adapter = nullptr;
		factory->EnumAdapters(0, &adapter);

		DXGI_ADAPTER_DESC adapterDesc;
		adapter->GetDesc(&adapterDesc);

		factory->Release();
		adapter->Release();

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
		//LARGE_INTEGER driverVersion;
		//adapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &driverVersion);
		//std::string major, minor, release, build;
		//major = std::to_string(HIWORD(driverVersion.HighPart));
		//minor = std::to_string(LOWORD(driverVersion.HighPart));
		//release = std::to_string(HIWORD(driverVersion.LowPart));
		//build = std::to_string(LOWORD(driverVersion.LowPart));

		// Fill Rendering Info
		auto& info = RenderingAPI::GetInfo();
		info.API = "DX11";
		//info.Version = std::string( major.c_str() + ""+ major.c_str());
		info.Vendor = vendor;
		info.Renderer = renderer;
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
		//glViewport(x, y, width, height);
	}
}