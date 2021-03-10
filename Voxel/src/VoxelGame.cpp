#include <Selene.h>
#include "Selene/EntryPoint.h"
#include "VoxelLayer.h"

namespace Voxel
{
	class VoxelGame : public Selene::Game
	{
	public:
		VoxelGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new VoxelLayer());
		}

		~VoxelGame()
		{
		}
	};
}

Selene::Game* Selene::CreateGame()
{
	return new Voxel::VoxelGame(Selene::RenderingAPI::API::OpenGL);
}