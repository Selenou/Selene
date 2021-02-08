#include <Selene.h>
#include "Selene/Main.h"
#include "VoxelLayer.h"

namespace Voxel
{
	class Voxel : public Selene::Game
	{
	public:
		Voxel(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new VoxelLayer());
		}

		~Voxel()
		{
		}
	};
}

Selene::Game* Selene::CreateGame()
{
	return new Voxel::Voxel(Selene::RenderingAPI::API::OpenGL);
}