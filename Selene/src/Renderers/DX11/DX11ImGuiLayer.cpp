#include "slnpch.h"
#include "DX11ImGuiLayer.h"
#include "Selene/Core/Game.h"

//tmp, always include Windows stuff before glfw
#include <d3d11.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

#include <imgui/backends/imgui_impl_dx11.h>

namespace Selene
{
	void DX11ImGuiLayer::Attach()
	{
		ImGuiLayer::Attach();

		Game& game = Game::GetInstance();
		auto window = static_cast<GLFWwindow*>(game.GetWindow().GetNativeWindow());

		// Init glfw, we should call something like ImGui_ImplGlfw_Init(window, true, GlfwClientApi_None) instead but it would require to put our hands in the example code of ImGui
		// As long as we dont use GlfwClientApi_OpenGL we are fine (here it uses GlfwClientApi_Vulkan)
		ImGui_ImplGlfw_InitForVulkan(window, true); 

		//ImGui_ImplDX11_Init(DX11Internal::GetDevice(), DX11Internal::GetDeviceContext());
	}

	void DX11ImGuiLayer::Detach()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void DX11ImGuiLayer::StartNewFrame()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DX11ImGuiLayer::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}