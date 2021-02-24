#pragma once

#include "EditorUI.h"

namespace Selene 
{
	class ConsolePanel : public EditorUI
	{
	public:
		virtual void Draw() override;
	};
}