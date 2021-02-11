#include "RaycasterLayer.h"

namespace Raycaster
{
	RaycasterLayer::RaycasterLayer()
		: Layer("Raycaster")
	{
		auto& window = Selene::Game::GetInstance().GetWindow();

		m_Camera = std::make_unique<Selene::Camera>();
		m_Camera->SetOrthographic(2.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

		



		float vertices[] =
		{
			-1.777f, -1.0f,  0.0f,		0.0f, 0.0f,
			1.777f, -1.0f,  0.0f,		1.0f, 0.0f,
			1.777f,  1.0f,  0.0f,		1.0f, 1.0f,
			-1.777f,  1.0f,  0.0f,		0.0f, 1.0f
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_SkyboxPipeline = Selene::Pipeline::Create();

		Selene::VertexBufferLayout skyboxLayout = { 
			{ "a_Position", Selene::DataType::Float3 },
			{ "a_Texcoord", Selene::DataType::Float2 },
		};

		m_SkyboxVbo = Selene::VertexBuffer::Create(vertices, sizeof(vertices));
		m_SkyboxVbo->SetLayout(skyboxLayout);
		m_SkyboxPipeline->BindVertexBuffer(m_SkyboxVbo);

		m_SkyboxEbo = Selene::IndexBuffer::Create(indices, sizeof(indices));
		m_SkyboxPipeline->BindIndexBuffer(m_SkyboxEbo);


		Selene::RenderingEngine::GetShaderLibrary()->Load("quad", "quad.vert", "quad.frag");
		m_SkyboxShader = Selene::RenderingEngine::GetShaderLibrary()->Get("quad");




		imageData = new GLubyte[dataSize];
		memset(imageData, 0, dataSize);

		//texture
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
		glBindTexture(GL_TEXTURE_2D, 0);

		//pbo
		glGenBuffers(1, &pboId);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, dataSize, 0, GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	void RaycasterLayer::Update(Selene::Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void RaycasterLayer::Render()
	{
		Selene::RenderingEngine::BeginFrame(*m_Camera);
		{
			glBindTexture(GL_TEXTURE_2D, textureId);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);

			// copy pixels from PBO to texture object
			// Use offset instead of ponter.
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

			// bind PBO to update pixel values
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);

			// map the buffer object into client's memory
			// Note that glMapBuffer() causes sync issue.
			// If GPU is working with this buffer, glMapBuffer() will wait(stall)
			// for GPU to finish its job. To avoid waiting (stall), you can call
			// first glBufferData() with NULL pointer before glMapBuffer().
			// If you do that, the previous data in PBO will be discarded and
			// glMapBuffer() returns a new allocated pointer immediately
			// even if GPU is still working with the previous data.
			glBufferData(GL_PIXEL_UNPACK_BUFFER, dataSize, 0, GL_STREAM_DRAW);
			GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

			if (ptr)
			{
				// update data directly on the mapped buffer
				UpdatePixels(ptr, dataSize);
				glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
			}

			// it is good idea to release PBOs with ID 0 after use.
			// Once bound with 0, all pixel operations behave normal ways.
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);




			// draw a point with texture
			glBindTexture(GL_TEXTURE_2D, textureId);
			
			m_SkyboxShader->Bind();
			m_SkyboxShader->SetUniform("u_ViewProjection", m_Camera->GetProjectionMatrix());

			Selene::RenderingEngine::Submit(m_SkyboxPipeline, m_SkyboxEbo->GetCount(), m_SkyboxVbo->GetCount());

			// unbind texture
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		Selene::RenderingEngine::EndFrame();
	}

	void RaycasterLayer::UpdatePixels(GLubyte* dst, int size)
	{
		static int color = 0xFF00FFFF;

		if (!dst)
			return;

		int* ptr = (int*)dst;

		// copy 4 bytes at once
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				*ptr = color;
				++ptr;
			}
			//color += 257;
		}
		//++color;
	}

	void RaycasterLayer::OnEvent(Selene::Event& event)
	{
		Selene::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}