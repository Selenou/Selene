#pragma once

#include "Selene/Audio/AudioSource.h"

namespace Selene
{
	struct AudioSourceComponent
	{
		AudioSource* Source;

		AudioSourceComponent() = default;
		AudioSourceComponent(const AudioSourceComponent&) = default;
	};
}