#pragma once

#include "AudioBuffer.h"
#include <AL/al.h>

namespace Selene
{
	class AudioUtils
	{
	public:
		static char* LoadWavFile(const std::string& file, ALsizei* frequency, ALsizei* size, ALenum* format);
	};
}