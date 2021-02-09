#include <Selene.h>
#include "Selene/Main.h"


namespace Raycaster
{
	class RaycasterGame : public Selene::Game
	{
	public:
		RaycasterGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{

		}

		~RaycasterGame()
		{
		}
	};
}

Selene::Game* Selene::CreateGame() 
{
	return new Raycaster::RaycasterGame(Selene::RenderingAPI::API::OpenGL);
}