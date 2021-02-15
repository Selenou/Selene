#include "slnpch.h"
#include "AudioSource.h"

namespace Selene
{
	AudioSource::AudioSource()
		: m_SourceID(-1), m_BufferID(-1), m_Gain(1.0f), m_Pitch(1.0f), m_IsLooping(false), m_Position(glm::vec3(0.0f)), m_Velocity(glm::vec3(0.0f))
	{
		SLN_INFO("Creating Audio Source");
		alGenSources(1, &m_SourceID);
	}

	AudioSource::~AudioSource()
	{
		SLN_INFO("Deleting Audio Source");
		alDeleteSources(1, &m_SourceID);
	}

	void AudioSource::SetBuffer(ALuint bufferId)
	{
		m_BufferID = bufferId;
		alSourcei(m_SourceID, AL_BUFFER, m_BufferID);
	}

	void AudioSource::SetGain(float gain) 
	{ 
		m_Gain = gain; 
		alSourcef(m_SourceID, AL_GAIN, m_Gain); 
	}

	void AudioSource::SetPitch(float pitch) 
	{
		m_Pitch = pitch;
		alSourcef(m_SourceID, AL_PITCH, m_Pitch); 
	}

	void AudioSource::SetIsLooping(bool isLooping) 
	{
		m_IsLooping = isLooping;
		alSourcei(m_SourceID, AL_LOOPING, m_IsLooping); 
	}

	void AudioSource::SetPosition(const glm::vec3& position) 
	{ 
		m_Position = position;
		alSource3f(m_SourceID, AL_POSITION, m_Position.x, m_Position.y, m_Position.z); 
	}

	void AudioSource::SetVelocity(const glm::vec3& velocity) 
	{ 
		m_Velocity = velocity;
		alSource3f(m_SourceID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z); 
	}
}