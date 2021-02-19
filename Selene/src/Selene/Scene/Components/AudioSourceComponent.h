#pragma once

#include "Selene/Audio/AudioSource.h"

namespace Selene
{
	struct AudioSourceComponent
	{
		AudioSource Source;
		AudioSourceComponent(const AudioSource& source) : Source(source) {}
	};
}