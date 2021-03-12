#pragma once
#include "Selene/Rendering/Context.h"
#include "DX11Device.h"
#include "Selene/Core/Game.h"

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
		inline static DX11Context* Get() { return static_cast<DX11Context*>(Game::GetInstance().GetWindow().GetRenderingContext()); }
		inline ID3D11Device* GetDevice() { return m_Device->GetDevice(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Device->GetDeviceContext(); }
		inline ID3D11RenderTargetView* GetBackBuffer() { return m_Device->GetBackBuffer(); }
	private:
		GLFWwindow* m_WindowHandle;
		std::unique_ptr<DX11Device> m_Device;
	};
}