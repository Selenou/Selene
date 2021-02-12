#pragma once

#include "AudioDevice.h"
//#include "AudioBuffer.h"

namespace Selene
{
	struct AudioEngineData
	{
		std::unique_ptr<AudioDevice> Device = nullptr;
		//std::unordered_map<std::string, AudioBuffer> m_BufferIDs;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class AudioEngine
	{
	public:
		static void Init();
		static void CreateAudioBuffer(const std::string& file);
	private:
		static inline AudioEngineData s_AudioEngineData;
	};
}