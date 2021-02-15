#include "slnpch.h"
#include "AudioUtils.h"

#include <fstream>

namespace Selene
{
	char* AudioUtils::LoadWavFile(const std::string& file, ALsizei* frequency, ALsizei* size, ALenum* format)
	{
		std::ifstream inputStream(file, std::ios::in | std::ios::binary);
		SLN_ASSERT(inputStream.is_open(), "Could not open file [%s]", file);

		char buffer[4];

		// RIFF chunk descriptor
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read RIFF of file [%s]", file);
		SLN_ASSERT(strncmp(buffer, "RIFF", 4) == 0, "File [%s] is not a valid WAVE file", file);
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read the chunk size of file [%s]", file);
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read WAVE of file [%s]", file);
		SLN_ASSERT(strncmp(buffer, "WAVE", 4) == 0, "File [%s] is not a valid WAVE file", file);

		// Fmt sub-chunk
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read the format chunk marker of file [%s]", file);
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read the length of format data (16) of file [%s]", file); 
		SLN_ASSERT(inputStream.read(buffer, 2), "Could not read the audio format of file [%s]", file);
		SLN_ASSERT(inputStream.read(buffer, 2), "Could not read the number of channels of file [%s]", file);
		uint16_t channels = (unsigned char)buffer[0] | (unsigned char)buffer[1] << 8;
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read the sample rate of file [%s]", file);
		*frequency = (unsigned char)buffer[0] | (unsigned char)buffer[1] << 8 | (unsigned char)buffer[2] << 16 | (unsigned char)buffer[3] << 24;
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read byte rate of file [%s]", file);
		SLN_ASSERT(inputStream.read(buffer, 2), "Could not read block align of file [%s]", file);
		SLN_ASSERT(inputStream.read(buffer, 2), "Could not bits per sample of file [%s]", file);
		uint16_t bitsPerSample = (unsigned char)buffer[0] | (unsigned char)buffer[1] << 8;

		// Data sub-chunk
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read DATA of file [%s]", file);
		SLN_ASSERT(strncmp(buffer, "data", 4) == 0, "File [%s] is not a valid WAVE file", file);
		SLN_ASSERT(inputStream.read(buffer, 4), "Could not read data size of file [%s]", file);		
		*size = (unsigned char)buffer[0] | (unsigned char)buffer[1] << 8 | (unsigned char)buffer[2] << 16 | (unsigned char)buffer[3] << 24;

		if (channels == 1)
		{
			if (bitsPerSample == 8)
			{
				*format = AL_FORMAT_MONO8;
			}
			else if (bitsPerSample == 16)
			{
				*format = AL_FORMAT_MONO16;
			}
		} 
		else if (channels == 2)
		{
			if (bitsPerSample == 8)
			{
				*format = AL_FORMAT_STEREO8;
			}
			else if (bitsPerSample == 16)
			{
				*format = AL_FORMAT_STEREO16;
			}
		}

		char* data = new char[*size];
		inputStream.read(data, *size);

		return data;
	}
}