#pragma once

#include "Core.h"

namespace Selene {

	class SELENE_API BaseApplication
	{
	public:
		BaseApplication();
		virtual ~BaseApplication();

		void Run();
	};

	BaseApplication* CreateApplication();
}