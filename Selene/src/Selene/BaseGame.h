#pragma once

#include "Core.h"

namespace Selene {

	class SELENE_API BaseGame
	{
	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();
	};

	BaseGame* CreateGame();
}