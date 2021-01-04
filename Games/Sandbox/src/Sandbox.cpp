#include <Selene.h>
#include "imgui/imgui.h"

class SandboxLayer : public Selene::Layer
{
public:
	SandboxLayer() : Layer("Sandbox") {}
public:
	virtual void Update() override {}
	virtual void RenderUI() override {}
};

class Sandbox : public Selene::Game
{
public:
	Sandbox(Selene::RenderingAPI::API renderingAPI)
		: Game(renderingAPI)
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new Sandbox(Selene::RenderingAPI::API::OpenGL);
}