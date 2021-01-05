#include <Selene.h>
#include "imgui/imgui.h"

//tmp + remove in premake
#include <glad/glad.h>
#include "Selene/Rendering/Shader.h"
#include "Selene/Rendering/Buffer.h"

class SandboxLayer : public Selene::Layer
{
public:
	SandboxLayer() : Layer("Sandbox") 
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		m_Vbo = Selene::VertexBuffer::Create(vertices, sizeof(vertices));
		m_Ebo = Selene::IndexBuffer::Create(indices, sizeof(indices));

		glCreateVertexArrays(1, &m_Vao); // direct state access (GL 4.5) : only creates the VAO but doesn't enable it

		// Set buffers that backs the vao (vbo + ebo)
		glVertexArrayVertexBuffer(m_Vao, 0, m_Vbo->GetID(), 0, 3 * sizeof(GLfloat));
		glVertexArrayElementBuffer(m_Vao, m_Ebo->GetID());

		glEnableVertexArrayAttrib(m_Vao, 0);
		glVertexArrayAttribFormat(m_Vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_Vao, 0, 0);

		m_Shader = Selene::Shader::Create("base.vert", "base.frag");
	}
public:
	virtual void Update() override 
	{
		glBindVertexArray(m_Vao);
		m_Shader->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	virtual void RenderUI() override {}

	unsigned int m_Vao;
	std::shared_ptr<Selene::Shader> m_Shader;
	std::shared_ptr<Selene::VertexBuffer> m_Vbo;
	std::shared_ptr<Selene::IndexBuffer> m_Ebo;
};

class Sandbox : public Selene::Game
{
public:
	Sandbox(Selene::RenderingAPI::API renderingAPI)
		: Game(renderingAPI)
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new Sandbox(Selene::RenderingAPI::API::OpenGL);
}