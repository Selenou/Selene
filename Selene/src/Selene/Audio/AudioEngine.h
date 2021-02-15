#pragma once

#include "AudioDevice.h"
#include "AudioBuffer.h"
#include "AudioSource.h"

namespace Selene
{
	struct AudioEngineData
	{
		std::unique_ptr<AudioDevice> Device = nullptr;
		std::unordered_map<std::string, AudioBuffer*> Buffers;
		std::vector<AudioSource*> Sources;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class AudioEngine
	{
	public:
		static void Init(); 
		static void Cleanup();
		static AudioSource* CreateAudioSource(const std::string& file);
		static void ReleaseAudioSource(AudioSource* source);
	private:
		static inline AudioEngineData s_AudioEngineData;
	};
}