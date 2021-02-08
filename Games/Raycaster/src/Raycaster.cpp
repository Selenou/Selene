#include <Selene.h>
#include "Selene/Main.h"


namespace Raycaster
{
	class Raycaster : public Selene::Game
	{
	public:
		Raycaster(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{

		}

		~Raycaster()
		{
		}
	};
}

Selene::Game* Selene::CreateGame() 
{
	return new Raycaster::Raycaster(Selene::RenderingAPI::API::OpenGL);
}