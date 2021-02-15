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

		for (auto& source : s_AudioEngineData.Sources)
		{
			delete source;
		}
	}

	AudioSource* AudioEngine::CreateAudioSource(const std::string& file)
	{
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

		AudioSource* source = new AudioSource();
		s_AudioEngineData.Sources.emplace_back(source);
		source->SetBuffer(buffer->GetID());

		return source;
	}

	void AudioEngine::ReleaseAudioSource(AudioSource* source)
	{
		auto it = std::find(s_AudioEngineData.Sources.begin(), s_AudioEngineData.Sources.end(), source);

		if (it != s_AudioEngineData.Sources.end())
		{
			s_AudioEngineData.Sources.erase(it);
			delete source;
		}
	}
}