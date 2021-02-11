#include <Selene.h>
#include "Selene/Main.h"
#include "RaycasterLayer.h"

namespace Raycaster
{
	class RaycasterGame : public Selene::Game
	{
	public:
		RaycasterGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new RaycasterLayer());
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