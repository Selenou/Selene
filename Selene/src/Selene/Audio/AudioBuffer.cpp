#include "slnpch.h"
#include "AudioBuffer.h"
#include "AudioUtils.h"

namespace Selene
{
	AudioBuffer::AudioBuffer(const std::string& file)
		:m_File(file)
	{
		alGenBuffers(1, &m_BufferID);
		char* data = AudioUtils::LoadWavFile(file, &m_Frequency, &m_Size, &m_Format);
		alBufferData(m_BufferID, m_Format, data, m_Size, m_Frequency);
		SLN_INFO("Creating Audio Buffer for [%s]", m_File);
		delete[] data;
	}

	AudioBuffer::~AudioBuffer()
	{
		SLN_INFO("Deleting Audio Buffer for [%s]", m_File);
		alDeleteBuffers(1, &m_BufferID);
	}
}