#include "slnpch.h"
#include "ImGuiLayer.h"
#include <imgui/imgui.h>

#include "Selene/Rendering/RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLImGuiLayer.h"

namespace Selene
{
	ImGuiLayer* ImGuiLayer::Create()
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL: 
				return new OpenGLImGuiLayer();
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}

	void ImGuiLayer::Attach()
	{
		IMGUI_CHECKVERSION();

		SLN_INFO("Initializing ImGui");
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		// Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;		// Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;			// Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	void ImGuiLayer::RenderUI()
	{
		//static bool show = true;
		//ImGui::ShowDemoWindow(&show);
	}
}