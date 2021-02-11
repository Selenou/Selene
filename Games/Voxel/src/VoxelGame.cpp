#include <Selene.h>
#include "Selene/Main.h"
#include "VoxelLayer.h"

#include <AL/alc.h>

namespace Voxel
{
	class VoxelGame : public Selene::Game
	{
	public:
		VoxelGame(Selene::RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new VoxelLayer());

			ALCdevice* openALDevice = alcOpenDevice(nullptr);
			if (!openALDevice)
				std::cerr << "ERROR: No device" << std::endl;

			ALCcontext* openALContext = alcCreateContext(openALDevice, nullptr);
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