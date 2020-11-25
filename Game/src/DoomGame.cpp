#include <Selene.h>
#include "imgui/imgui.h"

class TestLayer : public Selene::Layer
{
public:
	TestLayer() : Layer("Doom") {}
public:
	void Update() override {}
	void RenderUI() override {}
};

class DoomGame : public Selene::Game
{
public:
	DoomGame(Selene::RenderingAPI::API renderingAPI) 
		: Game(renderingAPI)
	{
		PushLayer(new TestLayer());
	}

	~DoomGame()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new DoomGame(Selene::RenderingAPI::API::OpenGL);
}