#pragma once
#include "Selene/Rendering/Context.h"
#include "DX11Device.h"

struct GLFWwindow;

namespace Selene
{
	class DX11Context : public Context
	{
	public:
		DX11Context(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle), m_Device(std::make_unique<DX11Device>()){}
	public:
		virtual void Init() override;
		virtual void Destroy() override {};
		virtual void SwapBuffers() override;
	public:
		inline ID3D11Device* GetDevice() { return m_Device->GetDevice(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Device->GetDeviceContext(); }
	private:
		GLFWwindow* m_WindowHandle;
		std::unique_ptr<DX11Device> m_Device;
	};
}