#pragma once

#include "AudioDevice.h"

namespace Selene
{
	struct AudioEngineData
	{
		std::unique_ptr<AudioDevice> Device = nullptr;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class AudioEngine
	{
	public:
		static void Init();
	private:
		static inline AudioEngineData s_AudioEngineData;
	};
}