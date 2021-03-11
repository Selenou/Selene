#include <Selene.h>
#include "Selene/EntryPoint.h"
#include "EditorLayer.h"

namespace Selene
{
	class SeleneEditor : public Game
	{
	public:
		SeleneEditor(RenderingAPI::API renderingAPI)
			: Game(renderingAPI)
		{
			PushLayer(new EditorLayer());
		}

		~SeleneEditor()
		{
		}
	};

	Game* CreateGame() 
	{
		return new SeleneEditor(RenderingAPI::API::DX11);
	}
}