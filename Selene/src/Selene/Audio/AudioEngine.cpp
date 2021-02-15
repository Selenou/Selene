#include "slnpch.h"
#include "AudioEngine.h"

#include <AL/al.h>

namespace Selene
{
	void AudioEngine::Init()
	{
		SLN_INFO("Initializing Audio Engine");
		s_AudioEngineData.Device = std::make_unique<AudioDevice>();
	}

	void AudioEngine::Cleanup()
	{
		for (auto& [key, bufferPtr] : s_AudioEngineData.Buffers)
		{
			delete bufferPtr;
		}
	}

	AudioSource* AudioEngine::CreateAudioSource(const std::string& file)
	{
		AudioSource* source = new AudioSource();
		AudioBuffer* buffer;

		if (s_AudioEngineData.Buffers.find(file) != s_AudioEngineData.Buffers.end())
		{
			buffer = s_AudioEngineData.Buffers.at(file);
			
		}
		else
		{
			buffer = new AudioBuffer(file);
			s_AudioEngineData.Buffers.emplace(file, buffer);
		}

		source->SetBuffer(buffer->GetID());

		return source;
	}
}