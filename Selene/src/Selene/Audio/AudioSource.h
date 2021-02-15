#pragma once

#include "AudioBuffer.h"

#include <glm/vec3.hpp>
#include <AL/al.h>

namespace Selene 
{
	class AudioSource
	{
	public:
		AudioSource();
		~AudioSource();
	public:
		inline void Play() { alSourcePlay(m_SourceID); }
		inline void Stop() { alSourceStop(m_SourceID); }
		inline void Pause() { alSourcePause(m_SourceID); }
	public:
		void SetBuffer(ALuint bufferId);
		void SetGain(float gain);
		void SetPitch(float pitch);
		void SetIsLooping(bool isLooping);
		void SetPosition(const glm::vec3& position);
		void SetVelocity(const glm::vec3& velocity);
	public:
		inline float GetGain() const { return m_Gain; }
		inline float GetPitch() const { return m_Pitch; }
		inline bool GetIsLooping() const { return m_IsLooping; }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetVelocity() const { return m_Velocity; }
	private:
		ALuint m_SourceID;
		ALuint m_BufferID;
		float m_Gain;
		float m_Pitch;
		bool m_IsLooping;
		glm::vec3 m_Position;
		glm::vec3 m_Velocity;
	};
}