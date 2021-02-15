#pragma once

#include <AL/al.h>

namespace Selene
{
	class AudioBuffer
	{
	public:
		AudioBuffer(const std::string& file);
		~AudioBuffer();
	public:
		ALuint GetID() { return m_BufferID; }
	private:
		ALuint m_BufferID;
		ALsizei m_Frequency;
		ALsizei m_Size;
		ALenum m_Format;
		std::string m_File;
	};
}