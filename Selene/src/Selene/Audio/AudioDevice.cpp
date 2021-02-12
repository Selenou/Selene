#include "slnpch.h"
#include "AudioDevice.h"
#include <AL/al.h>

namespace Selene
{
	AudioDevice::AudioDevice()
	{
		m_Device = alcOpenDevice(nullptr); // Sselect the "preferred device"
		SLN_ASSERT(m_Device, "Could not open playback device");
		
		m_Context = alcCreateContext(m_Device, nullptr);
		SLN_ASSERT(m_Context, "Could not create audio context");

		ALCboolean success = alcMakeContextCurrent(m_Context);
		SLN_ASSERT(success, "Could not set audio context");

		const ALchar* name = alcGetString(m_Device, ALC_ALL_DEVICES_SPECIFIER);
		SLN_INFO("Current playback device is [%s]", name);
	}

	AudioDevice::~AudioDevice()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_Context);
		alcCloseDevice(m_Device);
	}
}