#pragma once

namespace Selene
{
	class Timestep
	{
	public:
		Timestep() = default;
		Timestep(float time) : m_Time(time) {};
	public:
		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return m_Time * 1000.0f; }
		operator float() { return m_Time; }
	private:
		float m_Time = 0.0f;
	};

	class Time
	{
	public:
		static float GetTime();
	};
}