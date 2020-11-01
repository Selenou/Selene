#include "slnpch.h"
#include "GlfwWindow.h"

namespace Selene {

	Window* Window::Create(const WindowData& data)
	{
		return new GlfwWindow(data);
	}

	GlfwWindow::GlfwWindow(const WindowData & data)
	{
		Init(data);
	}

	GlfwWindow::~GlfwWindow()
	{
		Destroy();
	}

	void GlfwWindow::Init(const WindowData & data)
	{
		m_Data.Title = data.Title;
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;

		int success = glfwInit();
		SLN_ENGINE_INFO("Initializing Glfw");

		if (!success)
		{
			SLN_ENGINE_ERROR("Failed to initialize Glfw");
			//TODO : Manage error
		}

		m_Window = glfwCreateWindow(m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		SLN_ENGINE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (m_Window == NULL)
		{
			SLN_ENGINE_ERROR("Failed to create GLFW window");
			//TODO : Manage error
		}


		glfwMakeContextCurrent(m_Window);
		SetVSync(true);
	}

	void GlfwWindow::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void GlfwWindow::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void GlfwWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
	}

}
