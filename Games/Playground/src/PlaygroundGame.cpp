#include <Selene.h>
#include "Selene/Main.h"
#include "PlaygroundLayer.h"

namespace Playground
{
	class PlaygroundGame : public Selene::Game
	{
	public:
		PlaygroundGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new PlaygroundLayer());
		}

		~PlaygroundGame()
		{
		}
	};
}

Selene::Game* Selene::CreateGame() 
{
	return new Playground::PlaygroundGame(Selene::RenderingAPI::API::OpenGL);
}