#include <Selene.h>
#include "imgui/imgui.h"

class TestLayer : public Selene::Layer
{
public:
	TestLayer() : Layer("Doom") {}
public:
	virtual void Update() override {}
	virtual void RenderUI() override {}
};

class Doom : public Selene::Game
{
public:
	Doom(Selene::RenderingAPI::API renderingAPI) 
		: Game(renderingAPI)
	{
		PushLayer(new TestLayer());
	}

	~Doom()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new Doom(Selene::RenderingAPI::API::OpenGL);
}