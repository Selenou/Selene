#pragma once

#include "EditorPanel.h"

namespace Selene 
{
	class ConsolePanel : public EditorPanel
	{
	public:
		virtual void Draw() override;
	};
}