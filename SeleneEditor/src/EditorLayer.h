#pragma once

#include "Selene.h"
#include "Panels/EditorPanel.h"

namespace Selene
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
	protected:
		virtual void Attach() override;
		virtual void Update(Timestep ts) override;
		virtual void Render() override;
		virtual void RenderUI() override;
		virtual void OnEvent(Event& event) override;
	private:
		void DrawDockspace();
	private :
		std::vector<std::unique_ptr<EditorPanel>> m_Panels;
		std::unique_ptr<Camera> m_Camera;
		std::shared_ptr<Scene> m_Scene;
	};
}