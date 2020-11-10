#pragma once

#include "KeyCodes.h"

namespace Selene
{
	class Input
	{
	public:
		struct MousePosition
		{
			float X;
			float Y;
		};

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(KeyCode button);
		static MousePosition GetMousePosition();
	};
}