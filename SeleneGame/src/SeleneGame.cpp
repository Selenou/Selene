#include <Selene.h>
#include "Selene/EntryPoint.h"
#include "DebugLayer.h"
#include "GameLayer.h"

class SeleneGame : public Selene::Game
{
	public:
		SeleneGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new GameLayer());
			PushLayer(new DebugLayer());
		}

		~SeleneGame()
		{
		}
};

namespace Selene
{
	Selene::Game* CreateGame() 
	{
		return new SeleneGame(Selene::RenderingAPI::API::OpenGL);
	}
}