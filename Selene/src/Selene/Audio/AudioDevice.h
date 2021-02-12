#pragma once

#include <AL/alc.h>

namespace Selene
{
	class AudioDevice
	{
	public:
		AudioDevice();
		~AudioDevice();
	private:
		ALCdevice* m_Device;
		ALCcontext* m_Context;
	};
}