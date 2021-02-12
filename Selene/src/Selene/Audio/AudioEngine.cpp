#include "slnpch.h"
#include "AudioEngine.h"

namespace Selene
{
	void AudioEngine::Init()
	{
		SLN_INFO("Initializing Audio Engine");
		s_AudioEngineData.Device = std::make_unique<AudioDevice>();
	}
}