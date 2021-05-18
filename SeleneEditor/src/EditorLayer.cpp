#include "EditorLayer.h"
#include "Utils/IconsForkAwesome.h"

#include <imgui.h>

namespace Selene
{
	EditorLayer::EditorLayer() : Layer("Editor")
	{
		auto& window = Game::GetInstance().GetWindow();

		// Create Framebuffer
		//FramebufferSpecs fbSpecs;
		//fbSpecs.Width = 1280;
		//fbSpecs.Height = 720;
		//m_Framebuffer = Framebuffer::Create(fbSpecs);

		ImGuiIO& io = ImGui::GetIO();

		// Fonts
		// io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/quicksand/Quicksand-Bold.ttf", 17.0f);
		io.FontDefault = io.Fonts->AddFontDefault();
		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		static const ImWchar icon_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };
		io.Fonts->AddFontFromFileTTF("assets/fonts/forkawesome/forkawesome-webfont.ttf", 13.0f, &config, icon_ranges);

		//io.Fonts->AddFontFromFileTTF("assets/fonts/quicksand/Quicksand-Medium.ttf", 16.0f);

		m_Camera = std::make_unique<Camera>();
		m_Camera->SetOrthographic(2.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

		m_Scene = std::make_shared<Scene>();
		m_Dockspace = std::make_unique<Dockspace>(m_Scene);

		Actor cadence = m_Scene->CreateActor("CadenceBackgroundMusic");
		auto& sourceComponent = cadence.AddComponent<AudioSourceComponent>(*(AudioEngine::CreateAudioSource("assets/sounds/fairy.wav")));
		sourceComponent.Source.SetIsLooping(true);
		//sourceComponent.Source.Play();
	}

	void EditorLayer::Update(Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void EditorLayer::Render()
	{
		RenderingEngine::BeginFrame(*m_Camera);
		{
		
		}
		RenderingEngine::EndFrame();
	}

	void EditorLayer::RenderUI()
	{
		m_Dockspace->Draw();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<FramebufferResizeEvent>([=](FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}