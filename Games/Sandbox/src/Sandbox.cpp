#include <Selene.h>
#include "Selene/Main.h"
#include "SandboxLayer.h"

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