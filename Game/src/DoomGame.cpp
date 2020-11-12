#include <Selene.h>

#include "imgui/imgui.h"

class TestLayer : public Selene::Layer
{
public:
	TestLayer() : Layer("Doom") {}

	void RenderUI() override 
	{
		ImGui::Begin(m_Name.c_str());
		ImGui::Text(m_Name.c_str());
		ImGui::End();
	}
};

class DoomGame : public Selene::Game
{
public:
	DoomGame()
	{
		PushLayer(new TestLayer());
	}

	~DoomGame()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new DoomGame();
}