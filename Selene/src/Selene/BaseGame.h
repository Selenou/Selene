#pragma once

namespace Selene {

	class BaseGame
	{
	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();
	};

	BaseGame* CreateGame();
}