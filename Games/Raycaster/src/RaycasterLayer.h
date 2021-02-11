#pragma once

#include "Selene.h"
#include  <glad/glad.h>

namespace Raycaster
{
	class RaycasterLayer : public Selene::Layer
	{
	public:
		RaycasterLayer();
	public:
		virtual void Update(Selene::Timestep ts) override;
		virtual void Render() override;
		virtual void OnEvent(Selene::Event& event) override;
	private:
		void UpdatePixels(GLubyte* dst, int size);
	private :
		std::unique_ptr<Selene::Camera> m_Camera;


		std::shared_ptr<Selene::Shader> m_SkyboxShader;
		std::shared_ptr<Selene::VertexBuffer> m_SkyboxVbo;
		std::shared_ptr<Selene::IndexBuffer> m_SkyboxEbo;
		std::shared_ptr<Selene::Pipeline> m_SkyboxPipeline;

		int width = 1920;
		int height = 1080;
		int dataSize = width * height * 4;

		GLubyte* imageData = 0;
		uint32_t textureId;
		uint32_t pboId;
	};
}